#pragma once
#include "minecraft/src/common/world/phys/Vec3.hpp"

struct StateVectorComponent {
    Vec3 mPos;
    Vec3 mPosPrev;
    Vec3 mPosDelta;
};