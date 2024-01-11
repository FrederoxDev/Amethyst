#pragma once
#include "amethyst/Memory.h"

class Block;
class ChunkBlockPos;
class BlockPos;

class LevelChunk {
public:
    typedef BlockPos&(__thiscall* _getTopRainBlockPos)(LevelChunk* a1, ChunkBlockPos* a2, void* a3);

    // Found in BlockSource::getBlock(const BlockPos&)
    // 0x3909E80
    const Block* getBlock(const ChunkBlockPos& pos);
};