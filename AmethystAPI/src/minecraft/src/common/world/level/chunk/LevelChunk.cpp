#include "minecraft/src/common/world/level/chunk/LevelChunk.hpp"
#include <amethyst/Memory.hpp>

BlockActor* LevelChunk::getBlockEntity(const ChunkBlockPos& chunkPos)
{
    auto it = mBlockEntities.find(chunkPos);
    if (it == mBlockEntities.end()) return nullptr;
    return it->second.get();
}

// 1.21.0.3 - 40 ? 57 41 ? 48 83 ? ? 4C 8B ? 41 8B ? 48 8B ? 48 8B
void LevelChunk::setBlockVolume(const BlockVolume& blockVolume, uint32_t yOffset)
{
    using function = decltype(&LevelChunk::setBlockVolume);
    static auto func = std::bit_cast<function>(SigScan("40 ? 57 41 ? 48 83 ? ? 4C 8B ? 41 8B ? 48 8B ? 48 8B"));
    (this->*func)(blockVolume, yOffset);
}

const Block& LevelChunk::getBlock(const ChunkBlockPos& pos) const
{
    using function = decltype(&LevelChunk::getBlock);
    static auto func = std::bit_cast<function>(SigScan("48 83 EC ? 4C 8B 89 ? ? ? ? 4C 8B DA 44 0F B7 52 ? 41 0F B7 C2 66 C1 F8 ? 4C 0F BF C0 48 8B 81 ? ? ? ? 48 B9 ? ? ? ? ? ? ? ? 49 2B C1 48 C1 F8 ? 48 0F AF C1 4C 3B C0 73 ? 4B 8D 04 40 48 C1 E0 ? 4A 8B 4C 08 ? 48 85 C9 74 ? 0F B6 12 66 41 83 E2 ? 45 0F B6 43 ? 48 8B 01 66 C1 E2 ? 66 41 03 D0 66 C1 E2 ? 48 8B 40 ? 66 41 03 D2 48 83 C4 ? 48 FF 25 ? ? ? ? E8 ? ? ? ? 48 8B 00 48 8B 80 ? ? ? ? 48 83 C4 ? C3 CC CC CC CC CC CC CC CC CC CC CC 48 89 5C 24"));
    return (this->*func)(pos);
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