#pragma once
#include <stdint.h>

class Block;
class BlockPos;
class ChunkSource;

class BlockSource {
private:
    // Found via hooking ChestBlockActor::tick and reading qword0 on BlockSource param
    // offset: 0x5202EA8
    uintptr_t* vftable;

    // BlockSource::BlockSource - 0x3146820

public:
    const Block* getBlock(const BlockPos&);
};