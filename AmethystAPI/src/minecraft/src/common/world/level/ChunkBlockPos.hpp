#pragma once
#include <cstdint>
#include <functional>

#include <amethyst/Log.hpp>
#include "minecraft/src/common/world/level/BlockPos.hpp"
#include <minecraft/src/common/CommonTypes.hpp>
#include <minecraft/src-deps/core/math/Math.hpp>

class BlockPos;

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

namespace std {
template <>
    struct hash<ChunkBlockPos> {
        size_t operator()(const ChunkBlockPos& pos) const;
    };
     
    inline size_t hash<ChunkBlockPos>::operator()(const ChunkBlockPos& pos) const
    {
        // this is a mix of mce::Math::accumulate and std::hash
        // but I was failing to get the numbers used in the hash to match
        // 0x366000002E329 in v7 was 0x100000001B3 when using std::hash<uint8_t>
        // no other number types seemed to match, so manually reimpl it by hand

        size_t v7 = 0x366000002E329i64 * (pos.x ^ 0xCBF29CE484222325ui64) + 2654435769u;
        size_t v8 = ((v7 >> 2) 
            + 2654435769u  
            + (v7 << 6) 
            + 0x100000001B3i64 * ((pos.y >> 8) ^ (0x100000001B3i64 * (pos.y ^ 0xCBF29CE484222325ui64)))) ^ v7;

        size_t v10 = v8 ^ (0x366000002E329i64 * (pos.z ^ 0xCBF29CE484222325ui64) + (v8 << 6) + 2654435769u + (v8 >> 2));
        return v10;
    }
}

template <>
struct fmt::formatter<ChunkBlockPos> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }

    template <typename FormatContext>
    auto format(const ChunkBlockPos& pos, FormatContext& ctx)
    {
        return fmt::format_to(ctx.out(), "ChunkBlockPos(x: {}, y: {}, z: {})", pos.x, pos.y, pos.z);
    }
};