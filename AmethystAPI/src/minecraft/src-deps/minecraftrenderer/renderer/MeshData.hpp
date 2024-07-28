#pragma once
#include "glm/glm.hpp"
#include <vector>
#include <minecraft/src/common/world/phys/Vec3.hpp>

namespace mce {
    class MeshData {
    public:
        /* this + 0   */ std::byte padding0[8];
        /* this + 8   */ std::vector<Vec3> mPositions;
        /* this + 32  */ std::byte padding32[272 - 32];
    };
}

static_assert(sizeof(mce::MeshData) == 272);