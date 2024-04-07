#pragma once
#include <cstdint>
#include "minecraft/src-deps/renderer/MatrixStack.hpp"

namespace mce {
    class Camera {
    public:
        /* this + 0   */ MatrixStack viewMatrixStack;
        /* this + 64  */ MatrixStack worldMatrixStack;
        /* this + 128 */ MatrixStack projectionMatrixStack;
        /* this + 192 */ glm::tmat4x4<float> mInverseViewMatrix;
        /* this + 256 */ std::byte padding256[256];
    };
};

static_assert(sizeof(mce::Camera) == 512);