#pragma once
#include <memory>
#include <minecraft/src-deps/core/utility/buffer_span_mut.hpp>
#include <minecraft/src/common/world/level/block/Block.hpp>
#include <vector>

// Hols a span of blocks as well as information about their size. Used in worldgen.
class BlockVolume {
public:
    buffer_span_mut<const Block*> mBlocks;
    std::uint32_t mWidth;
    std::uint32_t mHeight;
    std::uint32_t mDepth;
    std::int32_t mDimensionBottom;
    const Block* mInitBlock;

    // Reimplemented
    BlockVolume(std::uint32_t width, std::uint32_t height, std::uint32_t depth, Block const* initBlock)
        : mWidth(width), mHeight(height), mDepth(depth), mDimensionBottom(0), mInitBlock(initBlock)
    {
        mBlocks = buffer_span_mut<const Block*>(width * depth * height);

        for (int i = 0; i < width * depth * height; i++) {
            this->mBlocks.mBegin[i] = initBlock;
        }
    }

    // Reimplemented
    size_t index(uint32_t x, uint32_t y, uint32_t z)
    {
        return (this->mDepth * x + z) * this->mHeight + y;
    }

    // Utility functions not in minecraft
    void set(const Block* block, uint32_t x, uint32_t y, uint32_t z)
    {
        this->mBlocks.mBegin[index(x, y, z)] = block;
    }

    const Block* get(uint32_t x, uint32_t y, uint32_t z)
    {
        return this->mBlocks.mBegin[index(x, y, z)];
    }
};