#include "ActorBlock.hpp"
#include <minecraft/src/common/world/level/BlockSource.hpp>

// 1.21.0.3 - Re-Implemented
void ActorBlock::neighborChanged(BlockSource& region, const BlockPos& pos, const BlockPos& neighborPos) const
{
    if (const BlockActor* blockActor = region.getBlockEntity(pos)) {
        blockActor->onNeighborChanged(region, pos);
    }
}

// 1.21.0.3 - Re-Implemented
void ActorBlock::triggerEvent(BlockSource& region, const BlockPos& pos, int b0, int b1) const
{
    BlockLegacy::triggerEvent(region, pos, b0, b1);
    if (const BlockActor* blockActor = region.getBlockEntity(pos)) {
        blockActor->triggerEvent(b0, b1);
    }
}