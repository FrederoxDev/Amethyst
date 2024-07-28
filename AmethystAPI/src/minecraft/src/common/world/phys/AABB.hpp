#pragma once
#include <minecraft/src/common/world/phys/Vec3.hpp>

class AABB {
public:
    Vec3 min;
    Vec3 max;

public:
    AABB();
    AABB(Vec3 min, Vec3 max);
    AABB(float minX, float minY, float minZ, float maxX, float maxY, float maxZ);
};