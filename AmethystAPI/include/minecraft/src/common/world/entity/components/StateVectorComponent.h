#pragma once

#include "common/world/phys/Vec3.h"

struct StateVectorComponent {
    Vec3 mPos;
    Vec3 mPosPrev;
    Vec3 mPosDelta;
};