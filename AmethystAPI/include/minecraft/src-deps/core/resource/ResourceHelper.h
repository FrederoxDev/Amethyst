#pragma once
#include "minecraft/src-deps/core/file/Path.h"

class ResourceLocation {
public:
    ResourceFileSystem mFileSystem;
private:
    Core::HeapPathBuffer mPath;
    HashType64 mPathHash;
    size_t mFullHash;

public:
    ResourceLocation();
    // 40 53 48 83 EC ? 33 C0 48 8B D9 89 01
    ResourceLocation(const Core::Path&);
    ResourceLocation(const Core::Path&, ResourceFileSystem);
    bool operator<(const ResourceLocation&) const;

    bool operator==(const ResourceLocation& rhs) const {
        return mPath == rhs.mPath && mFileSystem == rhs.mFileSystem;
    }

    bool operator!=(const ResourceLocation& rhs) const {
        return !(*this == rhs);
    }

    size_t hashCode() const {
        return mFullHash;
    }

    std::string getFileSystemName() const {
        return gsl::to_string(ResourceUtil::stringFromPath(mFileSystem));
    }

    void serialize(Json::Value&) const;
    void deserialize(const Json::Value&);
    Core::HeapPathBuffer getFullPath() const;
    const Core::HeapPathBuffer& getRelativePath() const;
    void setRelativePath(const Core::HeapPathBuffer&);
    HashedString getHashedPath() const;

private:
    void _computeHashes();
};