#pragma once
#include "core/math/Color.h"
#include "minecraft/common/world/level/BlockSource.h"
#include "minecraft/common/world/level/BlockPos.h"
#include "amethyst/Memory.h"

class Block {
public:
    /* Returns a ptr to the result parameter */
    Color* getMapColor(Color* result, BlockSource* a3, const BlockPos* a4) const;
};