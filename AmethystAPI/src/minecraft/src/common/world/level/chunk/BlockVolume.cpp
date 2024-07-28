#include "minecraft/src/common/world/level/chunk/BlockVolume.hpp"

BlockVolume::BlockVolume(buffer_span_mut<const Block*> blockSpan, std::uint32_t width, std::uint32_t height, std::uint32_t depth, Block const* initBlock)
    : mWidth(width), mHeight(height), mDepth(depth), mDimensionBottom(0), mBlocks(blockSpan), mInitBlock(initBlock)
{
    for (int i = 0; (uint32_t)i < width * depth * height; i++) {
        this->mBlocks.mBegin[i] = initBlock;
    }
}

size_t BlockVolume::index(uint32_t x, uint32_t y, uint32_t z)
{
    return (this->mDepth * x + z) * this->mHeight + y;
}

void BlockVolume::setBlock(const Block* block, uint32_t x, uint32_t y, uint32_t z)
{
    this->mBlocks.mBegin[index(x, y, z)] = block;
}

void BlockVolume::setBlock(const Block* block, BlockPos blockPos)
{
    this->mBlocks.mBegin[index(blockPos.x, blockPos.y, blockPos.z)] = block;
}

const Block* BlockVolume::getBlock(uint32_t x, uint32_t y, uint32_t z)
{
    return this->mBlocks.mBegin[index(x, y, z)];
}

const Block* BlockVolume::getBlock(BlockPos blockPos)
{
    return this->mBlocks.mBegin[index(blockPos.x, blockPos.y, blockPos.z)];
}