#include "minecraft/src/common/world/level/chunk/LevelChunk.hpp"
#include <amethyst/Memory.hpp>

BlockActor* LevelChunk::getBlockEntity(const ChunkBlockPos& chunkPos)
{
    auto it = mBlockEntities.find(chunkPos);
    if (it == mBlockEntities.end()) return nullptr;
    return it->second.get();
}

// 1.21.0.3 - 40 ? 57 41 ? 48 83 ? ? 4C 8B ? 41 8B ? 48 8B ? 48 8B
void LevelChunk::setBlockVolume(BlockVolume* blockVolume, unsigned int param2)
{
    using function = void(__thiscall*)(const LevelChunk*, BlockVolume* blockVolume, unsigned int param2);
    static auto func = reinterpret_cast<function>(SigScan("40 ? 57 41 ? 48 83 ? ? 4C 8B ? 41 8B ? 48 8B ? 48 8B"));
    func(this, blockVolume, param2);
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