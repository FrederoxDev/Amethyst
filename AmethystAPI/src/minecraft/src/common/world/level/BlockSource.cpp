#include "common/world/level/BlockSource.h"

const Block* BlockSource::getBlock(const BlockPos& pos)
{
    typedef const Block*(__thiscall * _getBlock)(const BlockPos&);
    return reinterpret_cast<_getBlock>(this->vftable[3])(pos);
}