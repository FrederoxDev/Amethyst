#pragma once
#include <fmt/core.h>

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
};

template <>
struct fmt::formatter<BlockPos> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }

    template <typename FormatContext>
    auto format(const BlockPos& pos, FormatContext& ctx)
    {
        return fmt::format_to(ctx.out(), "BlockPos(x: {}, y: {}, z: {})", pos.x, pos.y, pos.z);
    }
};