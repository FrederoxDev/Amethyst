#pragma once
#include "amethyst/Memory.h"

class Block;
class ChunkBlockPos;

class LevelChunk {
public:
    // Found in BlockSource::getBlock(const BlockPos&)
    // 0x3909E80
    const Block* getBlock(const ChunkBlockPos& pos);
};