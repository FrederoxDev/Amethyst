#pragma once
#include "minecraft/src/common/world/level/BlockPos.h"
#include <stdint.h>

class ChunkBlockPos {
public:
    uint8_t x;
    uint8_t y;
    uint16_t z;

    ChunkBlockPos(const BlockPos&);
};