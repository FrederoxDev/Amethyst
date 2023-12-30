#pragma once

#include "minecraft/src/common/world/level/ChunkBlockPos.h"
#include "minecraft/src/common/world/level/block/Block.h"
#include "minecraft/src/common/world/level/BlockPos.h"

#include "amethyst/Memory.h"

class LevelChunk {
public:
    typedef BlockPos&(__thiscall* _getTopRainBlockPos)(LevelChunk* a1, ChunkBlockPos* a2, void* a3);

    // Found in BlockSource::getBlock(const BlockPos&)
    // 0x3909E80
    const Block* getBlock(const ChunkBlockPos& pos);
};