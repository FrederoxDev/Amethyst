#pragma once
#include "amethyst/Memory.h"
#include "minecraft/src/common/world/level/BlockSource.h"
#include "minecraft/src/common/world/level/dimension/Dimension.h"
#include "minecraft/src/common/world/phys/Vec3.h"

class Actor {
private:
    uintptr_t** vtable;

public:
    Vec3* getPosition();
    Vec3* getHeadLookVector(float dist);

public:
    Dimension* getDimension();
};