#pragma once
#include "amethyst/Memory.hpp"
#include "minecraft/src-deps/core/math/Color.hpp"
#include "minecraft/src/common/world/level/BlockPos.hpp"
#include "minecraft/src/common/world/level/BlockSource.hpp"
#include "minecraft/src-deps/core/headerIncludes/gsl_includes.hpp"
#include "minecraft/src/common/world/level/block/components/BlockComponentStorage.hpp"
#include <minecraft/src/common/world/level/block/BlockState.hpp>

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
    /* this + 40  */ const uint16_t mData;
    /* this + 48  */ gsl::not_null<class BlockLegacy*> mLegacyBlock;
    /* this + 56  */ std::byte padding56[152];

public:
    // Circular dependency between this and BlockLegacy because of permutations vector
    // Have to explictly declare each thing..
    template <typename T>
    T getState(const BlockState& blockState) const;

    // Circular dependency between this and BlockLegacy because of permutations vector
    // Have to explictly declare each thing..
    template <typename T>
    gsl::strict_not_null<const Block*> setState(const BlockState& stateType, T value) const;

    mce::Color getMapColor(BlockSource& region, const BlockPos& pos) const;
};

static_assert(sizeof(Block) == 208);
static_assert(offsetof(Block, mLegacyBlock) == 48);