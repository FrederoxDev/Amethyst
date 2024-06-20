#include "minecraft/src/common/world/level/chunk/LevelChunk.hpp"

BlockActor* LevelChunk::getBlockEntity(const ChunkBlockPos& chunkPos)
{
    auto it = mBlockEntities.find(chunkPos);
    if (it == mBlockEntities.end()) return nullptr;
    return it->second.get();
}

std::shared_ptr<BlockActor> LevelChunk::getAndRemoveBlockActor(const ChunkBlockPos& pos)
{
    auto it = mBlockEntities.find(pos);
    if (it == mBlockEntities.end()) {
        Assert("LevelChunk::moveBlockEntity failed to find the actor at position {}", pos);
    }

    std::shared_ptr<BlockActor> result = std::move(it->second);
    mBlockEntities.erase(it);

    return result;
}

void LevelChunk::setBlockActor(const ChunkBlockPos& pos, std::shared_ptr<BlockActor> actorShared)
{
    mBlockEntities[pos] = std::move(actorShared);
}