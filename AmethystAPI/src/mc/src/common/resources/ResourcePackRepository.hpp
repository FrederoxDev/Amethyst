/// @symbolgeneration
#pragma once
#include <cstddef>
#include "mc/src-deps/core/utility/NonOwnerPointer.hpp"
#include "mc/src/common/resources/PackSourceFactory.hpp"
#include "mc/src/common/resources/CompositePackSource.hpp"
#include <amethyst/Imports.hpp>

namespace Core {
class FilePathManager;
}

class ResourcePack;
class ResourcePackRepository {
public:
    /* this + 0   */ Core::FilePathManager* mFilePathManager;
    /* this + 8   */ std::vector<std::unique_ptr<ResourcePack>> mAllResourcePacks;
    /* this + 32  */ std::byte padding32[32];
    /* this + 64  */ std::unique_ptr<CompositePackSource> mPackSource;
    /* this + 72  */ std::byte padding72[424 - 72];
    /* this + 424 */ PackSourceFactory& mPackSourceFactory;

	/// @signature {48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 55 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 4C 8B F1 33 F6, win-server}
    /// @signature {48 89 5C 24 ? 48 89 74 24 ? 55 57 41 54 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 48 8B F1 45 33 E4 0F 57 C9 F3 0F 7F 4D ? 41 8B FC}
    MC void _initializePackSource();

    /// @signature {48 89 5C 24 ? 57 48 83 EC ? 48 8B F9 48 8D 99 ? ? ? ? 48 89 5C 24 ? 48 8B CB FF 15 ? ? ? ? 85 C0 74 ? 8B C8 FF 15 ? ? ? ? 90 48 8B 07 48 8B CF 48 8B 80 ? ? ? ? FF 15 ? ? ? ? 84 C0 75 ? C6 87 ? ? ? ? ? EB ? 48 8B CF E8 ? ? ? ? 90}
    MC void requestReloadUserPacks();

    /// @signature {48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 56 41 57 48 83 EC ? 48 8B 59 ? 48 8B E9 48 3B 59}
    MC void _reloadUserPacks();
};

class ResourcePackStack;
namespace lambda {
// The lambda capture structure used in addFromUUID
struct Pack {
    Bedrock::NonOwnerPointer<ResourcePackRepository> repo;
    ResourcePackStack& stack;

	/// @signature {48 89 5C 24 ? 48 89 6C 24 ? 56 57 41 56 48 81 EC ? ? ? ? 48 8B F1 48 8B 01, win-server}
    /// @signature {48 89 5C 24 ? 55 56 57 48 81 EC ? ? ? ? 48 8B D9 48 8B 09}
    MC void addFromUUID(const PackIdVersion& version);
};
} // namespace lambda

