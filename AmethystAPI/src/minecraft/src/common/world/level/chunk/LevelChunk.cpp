#include "minecraft/src/common/world/level/chunk/LevelChunk.hpp"
#include <amethyst/Memory.hpp>

BlockActor* LevelChunk::getBlockEntity(const ChunkBlockPos& chunkPos)
{
    auto it = mBlockEntities.find(chunkPos);
    if (it == mBlockEntities.end()) return nullptr;
    return it->second.get();
}

// 1.21.0.3 - 40 ? 57 41 ? 48 83 ? ? 4C 8B ? 41 8B ? 48 8B ? 48 8B
void LevelChunk::setBlockVolume(BlockVolume* blockVolume, uint32_t yOffset)
{
    using function = decltype(&LevelChunk::setBlockVolume);
    static auto func = std::bit_cast<function>(SigScan("40 ? 57 41 ? 48 83 ? ? 4C 8B ? 41 8B ? 48 8B ? 48 8B"));
    (this->*func)(blockVolume, yOffset);
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