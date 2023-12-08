#pragma once
#include "core/math/Color.h"
#include "minecraft/src/common/world/level/BlockSource.h"
#include "minecraft/src/common/world/level/BlockPos.h"
#include "amethyst/Memory.h"

class Block {
public:
    /* Returns a ptr to the result parameter */
    typedef Color* (__thiscall* _getMapColor)(Block*, Color*, BlockSource*, const BlockPos*);
    Color* getMapColor(Color* result, BlockSource* a3, const BlockPos* a4) const;
};