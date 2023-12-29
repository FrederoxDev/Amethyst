#pragma once
#include "amethyst/Memory.h"
#include "minecraft/src-deps/core/math/Color.h"
#include "minecraft/src/common/world/level/BlockPos.h"
#include "minecraft/src/common/world/level/BlockSource.h"

class Block {
public:
    /* Returns a ptr to the result parameter */
    typedef mce::Color*(__thiscall* _getMapColor)(Block*, mce::Color*, BlockSource*, const BlockPos*);
    mce::Color* getMapColor(mce::Color* result, BlockSource* a3, const BlockPos* a4) const;
};