#include "minecraft/src-deps/core/resource/ResourceHelper.hpp"
#include "minecraft/src-deps/core/string/StringHash.hpp"

ResourceLocation::~ResourceLocation() {}

ResourceLocation::ResourceLocation() {
    mFileSystem = ResourceFileSystem::UserPackage;
    mPath = "";
    _computeHashes();
}

// Reimplemented in 1.20.71.1
ResourceLocation::ResourceLocation(const std::string& path) {
    mFileSystem = ResourceFileSystem::UserPackage;
    mPath = path;
    _computeHashes();
}

// Reimplemented in 1.20.71.1
void ResourceLocation::_computeHashes()
{
    HashType64 hash = HashedString::computeHash(mPath);
    mPathHash = hash;
    mFullHash = hash ^ (uint64_t)mFileSystem;
}
