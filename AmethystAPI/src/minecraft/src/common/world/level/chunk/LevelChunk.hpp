#pragma once
#include <unordered_map>
#include "amethyst/Memory.hpp"
#include <minecraft/src/common/world/level/ChunkBlockPos.hpp>

class Block;
class ChunkBlockPos;
class BlockPos;
class BlockActor;
class BlockSource;

class LevelChunk {
public:
    /* this + 0    */ std::byte padding0[4184];
    /* this + 4184 */ std::unordered_map<ChunkBlockPos, std::shared_ptr<BlockActor>> mBlockEntities;

public:
    BlockActor* getBlockEntity(const ChunkBlockPos& chunkPos);
    
    // 1.20.71.1 - 40 55 53 56 57 41 54 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 49 8B F1 4D 8B F8 48 8B DA
    // Found by caller of BlockLegacy::newBlockEntity
    std::shared_ptr<BlockActor> _createBlockEntity(const BlockPos& pos, BlockSource* currentSource, const Block& current, const Block& old);
    
    // Custom helper functions
    std::shared_ptr<BlockActor> getAndRemoveBlockActor(const ChunkBlockPos& pos);
    void setBlockActor(const ChunkBlockPos& pos, std::shared_ptr<BlockActor> actorShared);
};