#pragma once
#include <minecraft/src/common/world/level/Pos2d.hpp>

template <int Divisor>
struct DividedPos2d : public Pos2d {
    constexpr DividedPos2d() noexcept = default;

    constexpr DividedPos2d(int x, int z) noexcept : Pos2d(x, z) {}

    template<typename T>
    constexpr DividedPos2d(T const& pos) noexcept requires(requires(T const& t) {
        { t.x } -> std::convertible_to<int>; { t.z } -> std::convertible_to<int>; }) 
        : Pos2d(
              ((pos.x >> 31) - (pos.x >> 31) - pos.x ) / Divisor,
              ((pos.x >> 31) - (pos.x >> 31) - pos.x ) / Divisor
        ){}
};

using QuartPos2d = DividedPos2d<4>;