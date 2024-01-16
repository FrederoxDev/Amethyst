#include "common/world/level/ChunkBlockPos.h"

ChunkBlockPos::ChunkBlockPos(const BlockPos& pos)
{
    this->x = pos.x % 16;
    this->z = pos.z % 16;
    this->y = pos.y;
}