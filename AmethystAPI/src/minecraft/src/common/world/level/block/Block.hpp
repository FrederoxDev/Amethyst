#pragma once
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

typedef uint32_t BlockRuntimeId;

namespace mce {
class Color;
}
class BlockSource;
class BlockPos;
using DataID = unsigned short;

class Block : public BlockComponentStorage {
public:
    /* this + 40  */ const uint16_t mData;
    /* this + 48  */ gsl::not_null<class BlockLegacy*> mLegacyBlock;
    /* this + 56  */ std::byte padding56[140];
    /* this + 196 */ BlockRuntimeId mNetworkId;
    /* this + 204 */ bool mHasRuntimeId;


public:
    // Circular dependency between this and BlockLegacy because of permutations vector
    // Have to explictly declare each thing..
    template <typename T>
    T getState(const BlockState& blockState) const;

    // Circular dependency between this and BlockLegacy because of permutations vector
    // Have to explictly declare each thing..
    template <typename T>
    gsl::strict_not_null<const Block*> setState(const BlockState& stateType, T value) const;

    // 1.20.71.1 - Partial reimplementation using `BlockLegacy::getMapColor`
    // Needed because `BlockLegacy::getMapColor` is a protected function and the Block class
    // is its friend, how adorable..
    mce::Color getMapColor(BlockSource& region, const BlockPos& pos) const;

    bool canBeBuiltOver(BlockSource& region, const BlockPos&) const;

    BlockRuntimeId getRuntimeId() const {
        return mNetworkId;
    }

    bool isFenceBlock() const;
};

static_assert(sizeof(Block) == 208);
static_assert(offsetof(Block, mLegacyBlock) == 48);