#pragma once
#include <string>
#include "minecraft/src-deps/core/resource/ResourceUtil.h"
#include "minecraft/src-deps/core/file/Path.h"
#include "amethyst/Memory.h"

class ResourceLocation {
private:
    ResourceFileSystem mFileSystem;         // this + 0x0
    std::string mPath;                      // this + 0x8
    uint64_t mPathHash;                     // this + 0x28
    uint64_t mFullHash;                     // this + 0x30

public:
    ResourceLocation();
    ResourceLocation(const std::string& path);
};