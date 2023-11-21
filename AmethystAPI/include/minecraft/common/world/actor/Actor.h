#pragma once
#include "minecraft/common/world/level/BlockSource.h"
#include "minecraft/common/world/level/dimension/Dimension.h"
#include "Hook.h"

class Actor {
private:
    uintptr_t** vtable;

public:
    Dimension* getDimension();
    //const BlockSource* getDimensionBlockSourceConst();
};