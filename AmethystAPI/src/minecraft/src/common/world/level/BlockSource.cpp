#include "minecraft/src/common/world/level/BlockSource.hpp"
#include "amethyst/Memory.hpp"
#include "ChunkBlockPos.hpp"

void BlockSource::postGameEvent(Actor* source, const GameEvent& gameEvent, const BlockPos& originPos, const Block* affectedBlock)
{
	using function = decltype(&BlockSource::postGameEvent);
    static auto func = std::bit_cast<function>(SigScan("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B 01 49 8B D9"));
    (this->*func)(source, gameEvent, originPos, affectedBlock);
}

BlockActor* BlockSource::getBlockEntity(const BlockPos& pos)
{
    LevelChunk* levelChunk = getChunkAt(pos);
    if (!levelChunk) return nullptr;

    ChunkBlockPos inChunkPos(pos, mMinHeight);
    return levelChunk->getBlockEntity(inChunkPos);
}
