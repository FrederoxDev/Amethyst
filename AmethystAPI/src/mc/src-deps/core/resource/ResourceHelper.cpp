#include "mc/src-deps/core/resource/ResourceHelper.hpp"
#include "mc/src-deps/core/string/StringHash.hpp"
#include "ResourceHelper.hpp"

ResourceLocation::~ResourceLocation() {
}

ResourceLocation::ResourceLocation() {
	mFileSystem = ResourceFileSystem::UserPackage;
	mPath = "";
	_computeHashes();
}

ResourceLocation::ResourceLocation(const HashedString& path, ResourceFileSystem fileSystem) {
	mPath = path.getString();
	mFileSystem = fileSystem;
	_computeHashes();
}

// Reimplemented in 1.20.71.1
ResourceLocation::ResourceLocation(const std::string& path, ResourceFileSystem fileSystem) {
	mPath = path;
	mFileSystem = fileSystem;
	_computeHashes();
}

ResourceLocation::ResourceLocation(const char* path, ResourceFileSystem fileSystem) : ResourceLocation(std::string(path), fileSystem) {
}

// Reimplemented in 1.20.71.1
void ResourceLocation::_computeHashes() {
	HashType64 hash = HashedString::computeHash(mPath);
	mPathHash = hash;
	mFullHash = hash ^ (uint64_t)mFileSystem;
}
