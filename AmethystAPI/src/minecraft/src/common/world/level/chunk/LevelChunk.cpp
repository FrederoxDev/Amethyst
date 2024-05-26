#include "minecraft/src/common/world/level/chunk/LevelChunk.hpp"

BlockActor* LevelChunk::getBlockEntity(const ChunkBlockPos& chunkPos)
{
    using function = decltype(&LevelChunk::getBlockEntity);
    static auto func = std::bit_cast<function>(SigScan("40 53 56 57 48 83 EC ? 48 8B 01 48 8B FA"));
    return (this->*func)(chunkPos);
}
