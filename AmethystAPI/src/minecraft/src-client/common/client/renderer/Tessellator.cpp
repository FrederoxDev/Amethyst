#include "minecraft/src-client/common/client/renderer/Tessellator.h"

void Tessellator::begin(mce::PrimitiveMode mode, int maxVertices) {
    using function = void(__thiscall*)(Tessellator*, mce::PrimitiveMode, int);

    if (this->mTessellating) {
        throw std::exception("Already tessellating!");
    }

    static auto func = reinterpret_cast<function>(SigScan("48 89 5C 24 ? 56 48 83 EC ? 80 B9"));
    func(this, mode, maxVertices);
}

void Tessellator::vertex(float x, float y, float z) {
    using function = void(__thiscall*)(Tessellator*, float, float, float);
    static auto func = reinterpret_cast<function>(SigScan("40 57 48 81 EC ? ? ? ? 0F 29 7C 24 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 8B 81"));
    func(this, x, y, z);
}

void Tessellator::vertex(const Vec3& vec) {
    this->vertex(vec.x, vec.y, vec.z);
}

mce::Mesh* Tessellator::end(mce::Mesh* ret, uint64_t a3, std::string_view debugName, int a5) {
    using function = mce::Mesh*(__thiscall*)(Tessellator*, mce::Mesh*, uint64_t, std::string_view, int);
    static auto func = reinterpret_cast<function>(SigScan("48 8B C4 48 89 58 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 44 0F 29 40 ? 44 0F 29 48 ? 44 0F 29 90 ? ? ? ? 44 0F 29 98 ? ? ? ? 44 0F 29 A0 ? ? ? ? 44 0F 29 A8 ? ? ? ? 44 0F 29 B0 ? ? ? ? 44 0F 29 B8 ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4D 8B F9"));
    return func(this, ret, a3, debugName, a5);
}

void Tessellator::setPostTransformOffset(float xo, float yo, float zo) {
    this->mPostTransformOffset.x = xo;
    this->mPostTransformOffset.y = yo;
    this->mPostTransformOffset.z = zo;
}

void Tessellator::setPosTransformOffset(Vec3 v) {
    this->mPostTransformOffset = v;
}

Vec3 *Tessellator::getPostTransformOffset() {
    return &this->mPostTransformOffset;
}

void Tessellator::addPostTransformOffset(float x, float y, float z) {
    this->mPostTransformOffset.x += x;
    this->mPostTransformOffset.y += y;
    this->mPostTransformOffset.z += z;
}

void Tessellator::addPostTransformOffset(Vec3 v) {
    this->mPostTransformOffset = this->mPostTransformOffset + v;
}

void Tessellator::resetPostTransformScale() {
    this->mPostTransformScale = Vec3(1.0f, 1.0f, 1.0f);
}

void Tessellator::color(float r, float g, float b, float a) {
    struct PackedColors {
        union {
            struct {
                char r;
                char g;
                char b;
                char a;
            };
            unsigned int intValue;
        };
    };

    PackedColors result {};
    result.r = static_cast<char>(r * 255.0f);
    result.g = static_cast<char>(g * 255.0f);
    result.b = static_cast<char>(b * 255.0f);
    result.a = static_cast<char>(a * 255.0f);

    mNextColor = result.intValue;
}
