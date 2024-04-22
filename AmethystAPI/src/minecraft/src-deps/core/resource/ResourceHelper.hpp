#pragma once
#include "amethyst/Memory.hpp"
#include "minecraft/src-deps/core/file/Path.hpp"
#include "minecraft/src-deps/core/resource/ResourceUtil.hpp"
#include <string>
#include "minecraft/src-deps/core/semVer/SemVersion.hpp"
#include "minecraft/src-deps/core/utility/UUID.hpp"

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

struct PackIdVersion {
    mce::UUID mId;
    SemVersion mVersion;
    PackType mPackType;
};

class ResourceLocation {
public:
    ResourceFileSystem mFileSystem; // this + 0x0
    std::string mPath;              // this + 0x8
    uint64_t mPathHash;             // this + 0x28
    uint64_t mFullHash;             // this + 0x30

public:
    ~ResourceLocation();
    ResourceLocation();
    ResourceLocation(const std::string& path);

private:
    void _computeHashes();
};

static_assert(offsetof(ResourceLocation, mPath) == 8);