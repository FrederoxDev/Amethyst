#pragma once
#include "amethyst/Memory.h"
#include "minecraft/src-deps/core/math/Color.h"
#include "minecraft/src/common/world/level/BlockPos.h"
#include "minecraft/src/common/world/level/BlockSource.h"
#include "minecraft/src/common/world/level/block/BlockLegacy.h"

using DataID = unsigned short;

class Block {
public:
    uintptr_t** vtable;
    /* this + 8   */ const DataID mData;
    /* this + 10  */ std::byte padding10[6];
    /* this + 16  */ BlockLegacy* mLegacyBlock;
    /* this + 24  */ std::byte padding24[184];
};

static_assert(sizeof(Block) == 208);