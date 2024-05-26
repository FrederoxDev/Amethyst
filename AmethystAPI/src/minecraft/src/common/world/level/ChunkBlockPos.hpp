#pragma once
#include <cstdint>
#include <functional>

#include <amethyst/Log.hpp>
#include "minecraft/src/common/world/level/BlockPos.hpp"
#include <minecraft/src/common/CommonTypes.hpp>
#include <minecraft/src-deps/core/math/Math.hpp>

class ChunkBlockPos {
public:
    uint8_t x;
    uint8_t z;
    uint16_t y;

    ChunkBlockPos(uint8_t _x, uint16_t _y, uint8_t _z) 
        : x(_x), y(_y), z(_z) {};

    ChunkBlockPos(const BlockPos& pos, Height minDimensionHeight);

    bool operator==(const ChunkBlockPos& other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }
};