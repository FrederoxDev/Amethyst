#pragma once
#include <minecraft/src/common/world/level/BlockPos.hpp>


struct Pos2d {
    int x;
    int z;

    Pos2d(int x, int z) : x(x), z(z) {}
    Pos2d(BlockPos const& pos) : x(pos.x), z(pos.z) {}
    Pos2d() : x(0), z(0) {}
};