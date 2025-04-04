#pragma once

class Facing {
public:
    enum class Name : unsigned char {
        DOWN,
        UP,
        NORTH,
        SOUTH,
        WEST,
        EAST,
        MAX
    };

    static Facing::Name getOpposite(Facing::Name face);
    static Facing::Name getClockWise(Facing::Name face);
    static Facing::Name getCounterClockWise(Facing::Name face);
    static float getYAngle(Facing::Name face);
};

typedef Facing::Name FacingID;

#include <fmt/core.h>

template <>
struct fmt::formatter<FacingID> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }

    template <typename FormatContext>
    auto format(const FacingID& face, FormatContext& ctx)
    {
        switch (face) {
            case FacingID::DOWN:
                return fmt::format_to(ctx.out(), "down");
            case FacingID::UP:
                return fmt::format_to(ctx.out(), "up");
            case FacingID::NORTH:
                return fmt::format_to(ctx.out(), "north");
            case FacingID::SOUTH:
                return fmt::format_to(ctx.out(), "south");
            case FacingID::WEST:
                return fmt::format_to(ctx.out(), "west");
            case FacingID::EAST:
                return fmt::format_to(ctx.out(), "east");
            default:
                return fmt::format_to(ctx.out(), "unknown");
        }
    }
};