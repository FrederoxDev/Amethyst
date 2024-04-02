#pragma once
#include "minecraft/src/common/world/level/BlockPos.hpp"
#include <cstdint>

class ChunkBlockPos {
public:
    uint8_t x;
    uint8_t y;
    uint16_t z;

    ChunkBlockPos(const BlockPos&);
};