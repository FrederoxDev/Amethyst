#include "amethyst/runtime/resource/PackManager.hpp"
#include "amethyst/runtime/AmethystContext.hpp"
#include "amethyst/runtime/ModContext.hpp"
#include "amethyst/Log.hpp"

#include <resources/IResourcePackRepository.hpp>
#include <resources/ResourcePackStack.hpp>
#include <resources/ResourcePack.hpp>
#include <resources/PackSettingsFactory.hpp>
#include <resources/PackManifest.hpp>
#include <Core/Resource/PackIdVersion.hpp>

#include <winrt/Windows.Storage.h>
#include <Json.hpp>
#include <fstream>
#include <algorithm>

namespace fs = std::filesystem;

namespace Amethyst {

PackManager::PackManager(AmethystContext* amethyst) : mAmethyst(amethyst) {}
PackManager::~PackManager() = default;

const std::unordered_map<std::string, std::unordered_map<std::string, Pack>>& PackManager::GetPacks() const
{
    return mPacks;
}

void PackManager::RegisterNewPack(const Mod* owner, const std::string& path, PackType type, PackPriority priority)
{
    std::string key = owner->mInfo->GetVersionedName();

    fs::path packBasePath = owner->mInfo->Directory
        / (type == PackType::Resources ? "resource_packs" : "behavior_packs");
    fs::path manifestPath = packBasePath / path / "manifest.json";

    if (!fs::exists(manifestPath)) {
        Log::Warning("[Amethyst::PackManager] Cannot register pack — manifest not found: {}",
            manifestPath.generic_string());
        return;
    }

    std::ifstream manifestFile(manifestPath, std::ios::binary);
    if (!manifestFile.is_open()) {
        Log::Warning("[Amethyst::PackManager] Failed to open manifest for pack '{}' of '{}'",
            path, key);
        return;
    }
    std::string manifestContents((std::istreambuf_iterator<char>(manifestFile)),
        std::istreambuf_iterator<char>());

    nlohmann::json manifestJson;
    try {
        manifestJson = nlohmann::json::parse(manifestContents);
    }
    catch (const std::exception& e) {
        Log::Warning("[Amethyst::PackManager] Failed to parse manifest.json for '{}/{}': {}",
            key, path, e.what());
        return;
    }

    const auto& header = manifestJson["header"];
    if (!header.is_object() || !header.contains("uuid") || !header["uuid"].is_string()) {
        Log::Warning("[Amethyst::PackManager] Missing/invalid header.uuid in '{}/{}'", key, path);
        return;
    }
    const auto& versionVal = header["version"];
    if (!versionVal.is_array() || versionVal.size() != 3
        || !versionVal[0].is_number_unsigned()
        || !versionVal[1].is_number_unsigned()
        || !versionVal[2].is_number_unsigned()) {
        Log::Warning("[Amethyst::PackManager] Missing/invalid header.version in '{}/{}'", key, path);
        return;
    }

    mce::UUID packUuid = mce::UUID::fromString(header["uuid"].get<std::string>());
    SemVersion semVersion(
        versionVal[0].get<uint16_t>(),
        versionVal[1].get<uint16_t>(),
        versionVal[2].get<uint16_t>());

    auto& modSlot = mPacks[key];
    if (modSlot.contains(path)) return;
    modSlot.insert({path, Pack{owner, path, packUuid, semVersion, type, priority}});
}

// Shared logic for adding registered packs of a given type to a stack. Mirrors
// MC's BaseGamePackSlices::applyPackSlices (IDA 0x140721630): look up the
// ResourcePack via the repo, fetch PackSettings from the repo's factory,
// construct a PackInstance, hand it to the stack.
static void AddPacksOfTypeToStack(
    const std::unordered_map<std::string, std::unordered_map<std::string, Amethyst::Pack>>& packs,
    PackType wantType,
    const ::gsl::not_null<Bedrock::NonOwnerPointer<IResourcePackRepository>>& repository,
    ResourcePackStack& stack)
{
	Bedrock::NonOwnerPointer<const IResourcePackRepository> constNop(repository.get());
    ::gsl::not_null<Bedrock::NonOwnerPointer<const IResourcePackRepository>> constRepo(constNop);

    for (const auto& [modKey, modPacks] : packs) {
        // Sort by priority descending so higher-priority packs go in first.
        std::vector<std::pair<std::string, Amethyst::Pack>> sortedPacks(modPacks.begin(), modPacks.end());
        std::sort(sortedPacks.begin(), sortedPacks.end(), [](const auto& a, const auto& b) {
            return static_cast<int>(a.second.priority) > static_cast<int>(b.second.priority);
        });

        for (const auto& [path, pack] : sortedPacks) {
            if (pack.type != wantType) continue;

            PackIdVersion pid(pack.uuid, pack.version, pack.type);

            std::shared_ptr<ResourcePack> resourcePack = repository->getResourcePackForPackId(pid);
            if (!resourcePack) {
                Log::Warning("[Amethyst::PackManager] Repository has no pack for {}/{}", modKey, path);
                continue;
            }

            PackSettingsFactory& psf = repository->getPackSettingsFactory();
            PackSettings* settings = psf.getPackSettings(resourcePack->getManifest(), std::nullopt);

            ::gsl::not_null<std::shared_ptr<ResourcePack>> notNullPack(std::move(resourcePack));
            PackInstance instance(std::move(notNullPack), -1, false, settings);
            stack.add(std::move(instance), constRepo, false);
        }
    }
}

void PackManager::AddResourcePacksToStack(
    const ::gsl::not_null<Bedrock::NonOwnerPointer<IResourcePackRepository>>& repository,
    ResourcePackStack& stack)
{
    AddPacksOfTypeToStack(mPacks, PackType::Resources, repository, stack);
}

void PackManager::AddBehaviorPacksToStack(
    const ::gsl::not_null<Bedrock::NonOwnerPointer<IResourcePackRepository>>& repository,
    ResourcePackStack& stack)
{
    AddPacksOfTypeToStack(mPacks, PackType::Behavior, repository, stack);
}

} // namespace Amethyst
