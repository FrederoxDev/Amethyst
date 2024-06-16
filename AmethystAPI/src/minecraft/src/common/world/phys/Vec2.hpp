#pragma once
#include <fmt/core.h>
#include <fmt/format.h>

class Vec2 {
public:
    float x;
    float y;
};

template <>
struct fmt::formatter<Vec2> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }

    template <typename FormatContext>
    auto format(const Vec2& pos, FormatContext& ctx)
    {
        return fmt::format_to(ctx.out(), "Vec2(x: {}, y: {})", pos.x, pos.y);
    }
};