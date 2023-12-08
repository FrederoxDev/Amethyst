#include "minecraft/src/common/world/level/block/Block.h"

Color* Block::getMapColor(Color* a2, BlockSource* a3, const BlockPos* a4) const {
    typedef Color* (__thiscall* _getMapColor)(const Block*, Color*, BlockSource*, const BlockPos*);
    static auto func = reinterpret_cast<_getMapColor>(SlideAddress(0x34B46D0));
    return func(this, a2, a3, a4);
}