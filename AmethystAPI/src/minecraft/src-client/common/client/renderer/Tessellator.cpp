#include "minecraft/src-client/common/client/renderer/Tessellator.hpp"

void Tessellator::begin(mce::PrimitiveMode mode, int maxVertices) {
    using function = decltype(&Tessellator::begin);

    if (this->mTessellating) {
        throw std::exception("Already tessellating!");
    }

    static auto func = std::bit_cast<function>(SigScan("48 89 5C 24 ? 56 48 83 EC ? 80 B9"));
    (this->*func)(mode, maxVertices);
}

void Tessellator::vertex(float x, float y, float z) {
    using function = void(Tessellator::*)(float, float, float);
    static auto func = std::bit_cast<function>(SigScan("40 57 48 81 EC ? ? ? ? 0F 29 7C 24 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 8B 81"));
    (this->*func)(x, y, z);
}

void Tessellator::vertex(const Vec3& vec) {
    this->vertex(vec.x, vec.y, vec.z);
}

mce::Mesh Tessellator::end(uint64_t a3, std::string_view debugName, int a5) {
    using function = decltype(&Tessellator::end);
    static auto func = std::bit_cast<function>(SigScan("48 8B C4 48 89 58 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 44 0F 29 40 ? 44 0F 29 48 ? 44 0F 29 90 ? ? ? ? 44 0F 29 98 ? ? ? ? 44 0F 29 A0 ? ? ? ? 44 0F 29 A8 ? ? ? ? 44 0F 29 B0 ? ? ? ? 44 0F 29 B8 ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4D 8B F9"));
    return (this->*func)(a3, debugName, a5);
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

void Tessellator::beginOverride() {
    begin(mce::QuadList, 0);
    mVoidBeginEnd = true;
}

void Tessellator::clear() {
    using function = decltype(&Tessellator::clear);
    static auto func = std::bit_cast<function>(SigScan("48 83 EC ? C7 81 ? ? ? ? ? ? ? ? 4C 8B C9"));
    (this->*func)();
}

mce::Mesh Tessellator::endOverride(uint64_t a3, std::string_view debugName, int a5) {
    mVoidBeginEnd = false;
    return end(a3, debugName, a5);
}
