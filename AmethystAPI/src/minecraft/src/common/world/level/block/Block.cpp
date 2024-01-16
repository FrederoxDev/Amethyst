#include "common/world/level/block/Block.h"

#include "amethyst/Memory.h"

mce::Color* Block::getMapColor(mce::Color* a2, BlockSource* a3, const BlockPos* a4) const
{
    typedef mce::Color*(__thiscall * _getMapColor)(const Block*, mce::Color*, BlockSource*, const BlockPos*);
    static auto func = reinterpret_cast<_getMapColor>(SlideAddress(0x34B46D0)); // 1.20.30.02
    return func(this, a2, a3, a4);
}