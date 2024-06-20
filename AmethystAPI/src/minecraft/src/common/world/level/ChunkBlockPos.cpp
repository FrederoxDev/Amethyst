#include "minecraft/src/common/world/level/ChunkBlockPos.hpp"

ChunkBlockPos::ChunkBlockPos(const BlockPos& pos, Height minDimensionHeight)
{
    x = pos.x & 0xF;
    z = pos.z & 0xF;
    y = pos.y - minDimensionHeight;
}