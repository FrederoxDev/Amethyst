#pragma once
#include <cstdint>
#include "minecraft/src-deps/renderer/MatrixStack.h"

namespace mce {
    class Camera {
    public:
        /* this + 0   */ std::byte padding0[216];
        /* this + 216 */ glm::tmat4x4<float> mInverseViewMatrix;
        /* this + 280 */ std::byte padding280[232];
    };
};

static_assert(sizeof(mce::Camera) == 512);