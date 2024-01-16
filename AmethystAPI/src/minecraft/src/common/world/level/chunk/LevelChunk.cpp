#include "common/world/level/chunk/LevelChunk.h"

const Block* LevelChunk::getBlock(const ChunkBlockPos& pos)
{
    typedef const Block*(__thiscall * _getBlock)(LevelChunk * self, const ChunkBlockPos&);
    static auto func = reinterpret_cast<_getBlock>(SlideAddress(0x3909E80)); // 1.20.30.02
    return func(this, pos);
}