#pragma once
#include <functional>
#include <fmt/core.h>
#include <minecraft/src-deps/core/math/Math.hpp>
#include <minecraft/src-deps/core/utility/BinaryStream.hpp>

class BlockPos {
public:
    int x;
    int y;
    int z;

    BlockPos(int x, int y, int z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    BlockPos below() const
    {
        return {this->x, this->y - 1, this->z};
    }

    BlockPos above() const
    {
        return {this->x, this->y + 1, this->z};
    }

    constexpr size_t hashCode() const
    {
        // This implementation is completely guessed, please verify it for usage in actual game memory
        // only needed right now for mod memory, so impl hasn't been checked.
        size_t hash = 0;
        mce::Math::hash_accumulate(hash, x);
        mce::Math::hash_accumulate(hash, y);
        mce::Math::hash_accumulate(hash, z);
        return hash;
    }

    bool operator==(const BlockPos& other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }
};

// BinaryStream specialization
#include "minecraft/src-deps/core/utility/BinaryStream.hpp"

template <>
Bedrock::Result<BlockPos> ReadOnlyBinaryStream::get<BlockPos>();

template <>
void BinaryStream::write(BlockPos);

namespace std {
template <>
struct hash<BlockPos> {
    size_t operator()(const BlockPos& pos) const
    {
        return pos.hashCode();
    }
};
}

template <>
struct fmt::formatter<BlockPos> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }

    template <typename FormatContext>
    auto format(const BlockPos& pos, FormatContext& ctx)
    {
        return fmt::format_to(ctx.out(), "BlockPos(x: {}, y: {}, z: {})", pos.x, pos.y, pos.z);
    }
};