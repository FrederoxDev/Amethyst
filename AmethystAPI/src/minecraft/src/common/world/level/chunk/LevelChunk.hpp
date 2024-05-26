#pragma once
#include <unordered_map>
#include "amethyst/Memory.hpp"
#include <minecraft/src/common/world/level/ChunkBlockPos.hpp>

class Block;
class ChunkBlockPos;
class BlockPos;
class BlockActor;

class LevelChunk {
public:
    /* this + 0    */ std::byte padding0[4184];
    /* this + 4184 */ std::unordered_map<ChunkBlockPos, std::shared_ptr<BlockActor>> mBlockEntities;

public:
    BlockActor* getBlockEntity(const ChunkBlockPos& chunkPos);
};