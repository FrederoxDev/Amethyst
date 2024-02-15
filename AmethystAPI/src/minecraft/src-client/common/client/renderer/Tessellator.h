#pragma once
#include <cstddef>
#include "minecraft/src/common/world/phys/Vec3.h"
#include "amethyst/Memory.h"
#include <cstdint>

struct TessellatorQuadInfo {
public:
    /* this + 0  */ unsigned char facing;
    /* this + 1  */ unsigned char twoFace;
    /* this + 4  */ Vec3 centroid;
};

static_assert(sizeof(TessellatorQuadInfo) == 0x10);

namespace mce {
    enum PrimitiveMode : int {
        None = 0,
        QuadList = 1,
        TriangleList = 2,
        TriangleStrip = 3,
        LineList = 4,
        LineStrip = 5,
    };

    class MeshData {
        std::byte padding[0xf0];
    };

    class Mesh {
        std::byte padding0[536];
    };

    class MaterialPtr {
        std::byte padding0[1000]; // temp
    };

    static_assert(sizeof(Mesh) == 536);
}

class Tessellator {
public:
    /* this + 0   */ std::byte padding0[8];
    /* this + 8   */ mce::MeshData mMeshData;
    /* this + 248 */ std::byte padding248[128];
    /* this + 376 */ std::vector<TessellatorQuadInfo> mQuadInfoList;
    /* this + 400 */ std::byte padding400[84];
    /* this + 484 */ bool mNoColor;
    /* this + 485 */ std::byte padding485[47];
    /* this + 532 */ bool mTessellating;
    /* this + 533 */ std::byte padding533[28];
    /* this + 561 */ bool mBuildFaceData;

public:
    void begin(const mce::PrimitiveMode mode, const int maxVertices);
    void vertex(float x, float y, float z);
    mce::Mesh* end(mce::Mesh* ret, uint64_t a3, std::string_view debugName, int a5);
};