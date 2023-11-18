#pragma once
#include "core/math/Color.h"
#include "minecraft/common/world/level/BlockSource.h"
#include "minecraft/common/world/level/BlockPos.h"
#include "Hook.h"

class Block {
public:
    Color* getMapColor(Color* a2, BlockSource* a3, const BlockPos* a4);
};