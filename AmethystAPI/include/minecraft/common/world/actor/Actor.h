#pragma once
#include "minecraft/common/world/level/BlockSource.h"
#include "minecraft/common/world/level/dimension/Dimension.h"
#include "amethyst/Memory.h"
#include "minecraft/common/world/phys/Vec3.h"

class Actor {
private:
    uintptr_t** vtable;

public:
    Vec3* getPosition();

public:
    Dimension* getDimension();
};