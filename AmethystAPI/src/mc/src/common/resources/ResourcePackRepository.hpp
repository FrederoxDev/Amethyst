/// @symbols
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

    MC void _initializePackSource();

    MC void requestReloadUserPacks();

    MC void _reloadUserPacks();
};

class ResourcePackStack;
namespace lambda {
// The lambda capture structure used in addFromUUID
struct Pack {
    Bedrock::NonOwnerPointer<ResourcePackRepository> repo;
    ResourcePackStack& stack;

    MC void addFromUUID(const PackIdVersion& version);
};
} // namespace lambda

