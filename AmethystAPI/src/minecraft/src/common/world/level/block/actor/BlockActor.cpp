#include "minecraft/src/common/world/level/block/actor/BlockActor.hpp"

std::shared_ptr<BlockActor> BlockActorFactory::createBlockEntity(BlockActorType type, const BlockPos& pos, const BlockLegacy& block)
{
    // 1.20.71.1
    using function = decltype(&BlockActorFactory::createBlockEntity);
    static auto func = std::bit_cast<function>(SigScan("48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 49 8B F8 44 8B EA"));
    return func(type, pos, block);
}

void BlockActor::moveTo(const BlockPos& pos)
{
    mPosition = pos;
}
