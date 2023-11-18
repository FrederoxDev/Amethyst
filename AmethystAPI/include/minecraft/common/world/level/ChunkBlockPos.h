#pragma once
#include <stdint.h>
#include "minecraft/common/world/level/BlockPos.h"

class ChunkBlockPos {
public:
    uint8_t x;
    uint8_t y;
    uint16_t z;

    ChunkBlockPos(const BlockPos&);
};