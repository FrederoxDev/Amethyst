#pragma once
#include "amethyst/Memory.h"
#include "minecraft/common/core/file/Path.h"
#include "minecraft/common/core/resource/ResourceUtil.h"
#include <string>

class ResourceLocation {
private:
    ResourceFileSystem mFileSystem; // this + 0x0
    std::string mPath;              // this + 0x8
    uint64_t mPathHash;             // this + 0x28
    uint64_t mFullHash;             // this + 0x30

public:
    ResourceLocation();
    ResourceLocation(std::string  path);
};