#pragma once
#include "amethyst/Memory.hpp"
#include "minecraft/src-deps/core/file/Path.hpp"
#include "minecraft/src-deps/core/resource/ResourceUtil.hpp"
#include <string>

// Why does mojang define this in ResourceHelper?
enum class PackCategory : int {
    _Unknown,
    _RealmsUnknown,
    Standard,
    Premium,
    Custom,
    Subpack
};

enum class PackType : char {
    Invalid,
    Addon,
    Cached,
    CopyProtected,
    Behavior,
    PersonaPiece,
    Resources,
    Skins,
    WorldTemplate,
    Count
};

class ResourceLocation {
private:
    ResourceFileSystem mFileSystem; // this + 0x0
    std::string mPath;              // this + 0x8
    uint64_t mPathHash;             // this + 0x28
    uint64_t mFullHash;             // this + 0x30

public:
    ResourceLocation();
    ResourceLocation(const std::string& path);
};