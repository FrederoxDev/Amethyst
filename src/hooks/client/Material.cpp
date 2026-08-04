#ifdef CLIENT
#include <amethyst/runtime/ModContext.hpp>
#include <amethyst/runtime/utility/InlineHook.hpp>
#include <amethyst/runtime/resource/PackManager.hpp>
#include <amethyst/Log.hpp>

#include <RenderDragon/include/RenderDragon/Materials/CompiledMaterialManager.hpp>
#include <RenderDragon/include/RenderDragon/Materials/Definition/MaterialShared.hpp>

#include <Json.hpp>
#include <filesystem>
#include <fstream>
#include <mutex>
#include <sstream>
#include <unordered_map>

namespace fs = std::filesystem;

namespace Amethyst::ClientHooks::MaterialHooks {

static std::unordered_map<std::string, fs::path> sRegistry;
static std::once_flag sScanFlag;

static void ScanAllPacks()
{
	auto& packs = Amethyst::GetContext().mPackManager->GetPacks();
	for (const auto& [modKey, modPacks] : packs) {
		for (const auto& [packPath, pack] : modPacks) {
			if (pack.type != PackType::Resources) continue;
			fs::path materialsDir = pack.owner->mInfo->Directory / "resource_packs" / packPath / "materials";
			fs::path manifest = materialsDir / "materials.json";
			if (!fs::exists(manifest)) continue;

			std::ifstream f(manifest, std::ios::binary);
			if (!f.is_open()) continue;
			std::string contents((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());

			nlohmann::json doc;
			try { doc = nlohmann::json::parse(contents); }
			catch (const std::exception& e) {
				Log::Warning("[Amethyst::MaterialRegistry] {} parse failed: {}", manifest.generic_string(), e.what());
				continue;
			}

			const auto& materials = doc["materials"];
			if (!materials.is_array()) continue;
			for (const auto& entry : materials) {
				if (!entry.is_object()) continue;
				const auto& nameVal = entry["name"];
				const auto& fileVal = entry["file"];
				if (!nameVal.is_string() || !fileVal.is_string()) continue;
				std::string name = nameVal.get<std::string>();
				fs::path filePath = materialsDir / fileVal.get<std::string>();
				if (!fs::exists(filePath)) {
					Log::Warning("[Amethyst::MaterialRegistry] '{}' references missing {}", name, filePath.generic_string());
					continue;
				}
				sRegistry[name] = filePath;
			}
		}
	}
	Log::Info("[Amethyst::MaterialRegistry] Registered {} materials", sRegistry.size());
}

using namespace dragon::materials;
using SimplePassphrase = dragon::materials::definition::EncryptionVariants::SimplePassphrase;
using GetMaterialFn = std::shared_ptr<CompiledMaterialDefinition>
	(CompiledMaterialManager::*)(std::string, SimplePassphrase, bool);

Amethyst::InlineHook<GetMaterialFn> _CompiledMaterialManager_getMaterial;

std::shared_ptr<CompiledMaterialDefinition> CompiledMaterialManager_getMaterial(
	CompiledMaterialManager* self,
	std::string materialName,
	SimplePassphrase phrase,
	bool forceReload)
{
	std::call_once(sScanFlag, ScanAllPacks);

	auto it = sRegistry.find(materialName);
	if (it == sRegistry.end()) {
		return _CompiledMaterialManager_getMaterial(self, std::move(materialName), std::move(phrase), forceReload);
	}

	std::ifstream f(it->second, std::ios::binary);
	if (!f) {
		Log::Warning("[Amethyst::MaterialRegistry] Failed to open {}", it->second.generic_string());
		return _CompiledMaterialManager_getMaterial(self, std::move(materialName), std::move(phrase), forceReload);
	}
	std::stringstream ss; ss << f.rdbuf();
	const std::string blob = ss.str();

	std::function<bool(const std::string&, std::string&)> loadFn =
		[&blob](const std::string&, std::string& out) { out = blob; return true; };
	CompiledMaterialResource cmr;
	if (!self->_loadCompiledMaterialResource(materialName, cmr, phrase, loadFn)) {
		Log::Warning("[Amethyst::MaterialRegistry] _loadCompiledMaterialResource failed for {}", materialName);
		return {};
	}
	return cmr.mMaterial;
}

void Initialize()
{
	auto& hooks = Amethyst::GetHookManager();
	HOOK(CompiledMaterialManager, getMaterial);
}

}
#endif
