#pragma once
#include "minecraft/common/world/level/BlockPos.h"
#include <cstdint>

class ChunkBlockPos {
public:
    uint8_t x;
    uint8_t y;
    uint16_t z;

    ChunkBlockPos(const BlockPos&);
};