#pragma once
#include <cstddef>
#include "minecraft/src/common/world/phys/Vec3.h"
#include "amethyst/Memory.h"
#include <cstdint>
#include "glm/glm.hpp"
#include "minecraft/src-deps/minecraftrenderer/renderer/MeshData.h"
#include "minecraft/src-deps/minecraftrenderer/renderer/Mesh.h"

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
}

//is_virtual = False
//hide_vtable = False
//struct_size = 562
//
//# (Type, Name, Size (in bytes), Offset (in bytes))
//struct = [
//("mce::MeshData", "mMeshData", 0xf0, 8),
//("bool", "mNoColor", 1, 484),
//("bool", "mTessellating", 1, 532),
//("bool", "mBuildFaceData", 1, 561),
//("std::vector<TessellatorQuadInfo>", "mQuadInfoList", 24, 376),
//("Vec3", "mPostTransformOffset", 12, 348),
//("unsigned int", "mCount", 4, 552),
//("bool", "mIsFormatFixed", 1, 0),
//("bool", "mApplyTransform", 1, 416),
//("Vec3", "mPostTransformScale", 12, 360)
//]

class Tessellator {
public:
        /* this + 0   */ bool mIsFormatFixed;
        /* this + 1   */ std::byte padding1[7];
        /* this + 8   */ mce::MeshData mMeshData;
        /* this + 248 */ std::byte padding248[100];
        /* this + 348 */ Vec3 mPostTransformOffset;
        /* this + 360 */ Vec3 mPostTransformScale;
        /* this + 372 */ std::byte padding372[4];
        /* this + 376 */ std::vector<TessellatorQuadInfo> mQuadInfoList;
        /* this + 400 */ std::byte padding400[16];
        /* this + 416 */ bool mApplyTransform;
        /* this + 417 */ std::byte padding417[67];
        /* this + 484 */ bool mNoColor;
        /* this + 485 */ std::byte padding485[47];
        /* this + 532 */ bool mTessellating;
        /* this + 533 */ std::byte padding533[19];
        /* this + 552 */ unsigned int mCount;
        /* this + 556 */ std::byte padding556[5];
        /* this + 561 */ bool mBuildFaceData;

public:
    void begin(mce::PrimitiveMode mode, int maxVertices);

    void vertex(float x, float y, float z);
    void vertex(const Vec3&);

    void setPostTransformOffset(float xo, float yo, float zo);
    void setPosTransformOffset(Vec3 v);
    Vec3* getPostTransformOffset();
    void addPostTransformOffset(float x, float y, float z);
    void addPostTransformOffset(Vec3 v);

    void resetPostTransformScale();

    mce::Mesh* end(mce::Mesh* ret, uint64_t a3, std::string_view debugName, int a5);
};