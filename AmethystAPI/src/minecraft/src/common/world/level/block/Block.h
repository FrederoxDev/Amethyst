#pragma once
#include "amethyst/Memory.h"
#include "minecraft/src-deps/core/math/Color.h"
#include "minecraft/src/common/world/level/BlockPos.h"
#include "minecraft/src/common/world/level/BlockSource.h"
#include "minecraft/src/common/world/level/block/BlockLegacy.h"
#include "minecraft/src-deps/core/headerIncludes/gsl_includes.h"
#include "minecraft/src/common/world/level/block/components/BlockComponentStorage.h"

//is_virtual = True
//hide_vtable = False
//struct_size = 208
//
//# (Type, Name, Size (in bytes), Offset (in bytes))
//struct = [
//("gsl::not_null<BlockLegacy*>", "mLegacyBlock", 8, 0x30),
//]

using DataID = unsigned short;

class Block : public BlockComponentStorage {
public:
    /* this + 40  */ std::byte padding40[8];
    /* this + 48  */ gsl::not_null<BlockLegacy*> mLegacyBlock;
    /* this + 56  */ std::byte padding56[152];
};

static_assert(sizeof(Block) == 208);
static_assert(offsetof(Block, mLegacyBlock) == 48);