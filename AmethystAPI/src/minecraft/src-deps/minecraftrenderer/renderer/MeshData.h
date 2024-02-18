#pragma once
#include "glm/glm.hpp"
#include <vector>

namespace mce {
    class MeshData {
        /* this + 0   */ std::byte padding0[8];
        /* this + 8   */ std::vector<float> mPositions;
        /* this + 32  */ std::byte padding32[208];
    };
}