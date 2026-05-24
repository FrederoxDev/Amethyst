#pragma once
#include <Core/Utility/NonOwnerPointer.hpp>
#include "amethyst/runtime/mod/Mod.hpp"
#include "amethyst/Memory.hpp"
#include <Platform/UUID.hpp>
#include <Core/SemVer/SemVersion.hpp>
#include <Core/Resource/PackType.hpp>

class AmethystContext;
class ResourcePackStack;
class ResourcePackRepository;
class IResourcePackRepository;

namespace Amethyst {
enum class PackPriority {
    Lowest = 0,
    Lower = 1,
    Low = 2,
    Normal = 3,
    High = 4,
    Higher = 5,
    ExtremelyHigh = 6
};

struct Pack {
    const Mod* owner;
    std::string path;
    mce::UUID uuid;
    SemVersion version;
    PackType type;
    PackPriority priority;
};

class PackManager {
public:
    PackManager(AmethystContext* amethyst);
    PackManager(const PackManager&) = delete;
    PackManager(PackManager&&) = delete;
    PackManager& operator=(const PackManager&) = delete;
    PackManager& operator=(PackManager&&) = delete;
    ~PackManager();

    void RegisterNewPack(const Mod* owner, const std::string& path, PackType type, PackPriority priority = PackPriority::Normal);
    const std::unordered_map<std::string, std::unordered_map<std::string, Pack>>& GetPacks() const;
    void AddResourcePacksToStack(const ::gsl::not_null<Bedrock::NonOwnerPointer<IResourcePackRepository>>& repository, ResourcePackStack& stack);
    void AddBehaviorPacksToStack(const ::gsl::not_null<Bedrock::NonOwnerPointer<IResourcePackRepository>>& repository, ResourcePackStack& stack);

private:
    AmethystContext* mAmethyst;
    friend class AmethystContext;

private:
    std::unordered_map<std::string, std::unordered_map<std::string, Pack>> mPacks;
};
}