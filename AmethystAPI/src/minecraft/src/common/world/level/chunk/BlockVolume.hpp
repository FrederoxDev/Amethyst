#pragma once
#include "../block/Block.hpp"
#include <memory>
#include <vector>

class Block;

template <typename T>
class buffer_span_mut {
public:
    T* mBegin;
    T* mEnd;

    buffer_span_mut() : mBegin(nullptr), mEnd(nullptr) {}

    buffer_span_mut(T* const begin, T* const end) : mBegin(begin), mEnd(end) {}

    buffer_span_mut(std::vector<T>& buffer) : buffer_span_mut(buffer.data(), &buffer.data()[buffer.size()]) {}
};

class BlockVolume {
public:
    buffer_span_mut<const Block*> mBlocks;
    std::uint32_t mWidth;
    std::uint32_t mHeight;
    std::uint32_t mDepth;
    std::int32_t mDimensionBottom;
    const Block* mInitBlock;

    // Not part of vanilla. Using this to manage the data temporarily
    std::vector<const Block*> _blocksHolder;

    BlockVolume(std::uint32_t width, std::uint32_t height, std::uint32_t depth, Block const* initBlock)
        : mWidth(width), mHeight(height), mDepth(depth), mDimensionBottom(0), mInitBlock(initBlock)
    {
        _blocksHolder = std::vector<const Block*>(width * depth * height);

        for (int i = 0; i < width * depth * height; i++) {
            _blocksHolder[i] = initBlock;
        }

        mBlocks = buffer_span_mut(_blocksHolder);
    }
};