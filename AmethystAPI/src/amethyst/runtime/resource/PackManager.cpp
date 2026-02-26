#include "amethyst/runtime/resource/PackManager.hpp"
#include "amethyst/runtime/AmethystContext.hpp"
#include "mc/src-client/common/client/game/MinecraftGame.hpp"
#include "mc/src/common/resources/ResourcePackRepository.hpp"
#include <winrt/Windows.Storage.h>
#include <fstream>
#include <amethyst/runtime/ModContext.hpp>

Amethyst::PackManager::PackManager(AmethystContext* amethyst) : 
    mAmethyst(amethyst)
{}

Amethyst::PackManager::~PackManager() {}

void Amethyst::PackManager::RegisterNewPack(const Mod* owner, const std::string& path, PackType type, PackPriority priority)
{
    auto& platform = Amethyst::GetPlatform();
    std::string key = owner->mInfo->GetVersionedName();
    fs::path resourcesPath = platform.GetAmethystFolder() / "mods" / key / "resource_packs";
    fs::path behaviorPath = platform.GetAmethystFolder() / "mods" / key / "behavior_packs";
    auto& packBasePath = (type == PackType::Resources) ? resourcesPath : behaviorPath;

	// Check if the mod is on the list of packs, if not add it
	if (!mPacks.contains(key)) {
        mPacks[key] = {};
	}

	// Check if the pack path is already registered for this mod
    if (mPacks[key].contains(path)) {
		  return;
    }

    auto manifestPath = packBasePath / path / "manifest.json";

    // Check if the pack contains a manifest.json
    if (!fs::exists(manifestPath)) {
        return;
    }

    // Try to read the manifest.json to ensure it's valid
    std::ifstream manifestFile(manifestPath, std::ios::binary);
    Assert(manifestFile.is_open(), "Failed to open manifest.json for pack '{}' of '{}'", owner->mInfo->Directory.generic_string(), key);
    std::string manifestContents((std::istreambuf_iterator<char>(manifestFile)), std::istreambuf_iterator<char>());

    // Try to parse the manifest.json
    auto manifestJson = nlohmann::json::parse(manifestContents);
    if (!manifestJson.is_object()) {
        return;
    }

    // Ensure it has a header object
    auto& header = manifestJson["header"];
    if (!header.is_object()) {
        return;
    }

    // Ensure it has a uuid string in the header
    auto& uuid = header["uuid"];
    if (!uuid.is_string()) {
        return;
    }
    
    // Ensure it has a version array in the header
    auto& version = header["version"];
    if (!version.is_array() || version.size() != 3 || !version[0].is_number_unsigned() || !version[1].is_number_unsigned() || !version[2].is_number_unsigned()) {
        return;
    }

    mce::UUID packUuid = mce::UUID::fromString(uuid.get<std::string>());
    SemVersion semVersion = {version[0].get<uint16_t>(), version[1].get<uint16_t>(), version[2].get<uint16_t>()};

	// Insert the new pack
    mPacks[key].insert({path, Pack{owner, path, packUuid, semVersion, type, priority}});
}

const std::unordered_map<std::string, std::unordered_map<std::string, Amethyst::Pack>>& Amethyst::PackManager::GetPacks() const
{
	return mPacks;
}

void Amethyst::PackManager::AddResourcePacksToStack(const Bedrock::NonOwnerPointer<ResourcePackRepository>& repository, ResourcePackStack& stack)
{
    // Iterate over all registered packs
    // for (auto& [nameVer, packs] : mPacks) {
    //     // Sort packs by priority (highest priority first)
    //     std::vector<std::pair<std::string, Pack&>> sortedPacks(packs.begin(), packs.end());
    //     std::ranges::sort(sortedPacks, [](const auto& a, const auto& b) {
    //         return static_cast<int>(a.second.priority) > static_cast<int>(b.second.priority);
    //     });

    //     for (auto& [path, pack] : sortedPacks) {
    //         if (pack.type != PackType::Resources)
    //             continue;
    //         // Add the pack to the stack
    //         // Workaround for lambda capture
    //         lambda::Pack lambdaPack{repository, stack};
    //         lambdaPack.addFromUUID({pack.uuid, pack.version});
    //     }
    // }
}

void Amethyst::PackManager::AddBehaviorPacksToStack(const Bedrock::NonOwnerPointer<ResourcePackRepository>& repository, ResourcePackStack& stack)
{
    // Iterate over all registered packs
    // for (auto& [nameVer, packs] : mPacks) {
    //     // Sort packs by priority (highest priority first)
    //     std::vector<std::pair<std::string, Pack&>> sortedPacks(packs.begin(), packs.end());
    //     std::ranges::sort(sortedPacks, [](const auto& a, const auto& b) {
    //         return static_cast<int>(a.second.priority) > static_cast<int>(b.second.priority);
    //     });

    //     for (auto& [path, pack] : sortedPacks) {
    //         if (pack.type != PackType::Behavior)
    //             continue;
    //         // Add the pack to the stack
    //         // Workaround for lambda capture
    //         lambda::Pack lambdaPack{repository, stack};
    //         lambdaPack.addFromUUID({pack.uuid, pack.version});
    //     }
    // }
}
