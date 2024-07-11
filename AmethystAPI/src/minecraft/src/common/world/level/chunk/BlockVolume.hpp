#pragma once
#include <memory>
#include <minecraft/src-deps/core/utility/buffer_span_mut.hpp>
#include <minecraft/src/common/world/level/BlockPos.hpp>
#include <minecraft/src/common/world/level/block/Block.hpp>
#include <vector>

// Holds a span of blocks as well as information about their size. Used in worldgen.
class BlockVolume {
public:
    buffer_span_mut<const Block*> mBlocks;
    std::uint32_t mWidth;
    std::uint32_t mHeight;
    std::uint32_t mDepth;
    std::int32_t mDimensionBottom;
    const Block* mInitBlock;

    // Reimplemented
    BlockVolume(buffer_span_mut<const Block*> blockSpan, std::uint32_t width, std::uint32_t height, std::uint32_t depth, Block const* initBlock);

    // Reimplemented
    size_t index(uint32_t x, uint32_t y, uint32_t z);

    // Utility functions not in minecraft
    void setBlock(const Block* block, uint32_t x, uint32_t y, uint32_t z);
    void setBlock(const Block* block, BlockPos blockPos);

    const Block* getBlock(uint32_t x, uint32_t y, uint32_t z);
    const Block* getBlock(BlockPos blockPos);
};