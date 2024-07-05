#include "minecraft/src/common/world/phys/AABB.hpp"

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

AABB::AABB()
{
}

AABB::AABB(Vec3 min, Vec3 max) 
	: min(min), max(max) {}

AABB::AABB(float minX, float minY, float minZ, float maxX, float maxY, float maxZ)
	: min(minX, minY, minZ), max(maxX, maxY, maxZ) {}
