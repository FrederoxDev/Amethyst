#pragma once
#include <minecraft/src-deps/core/string/StringHash.hpp>

class CompoundTag;

class BlockState {
public:
    struct StateListNode {
        BlockState::StateListNode* mNext;
        BlockState::StateListNode* mPrev;
        BlockState* mState;
    };

public:
    const uint64_t mID;
    const uint64_t mVariationCount;
    const HashedString mName;
    BlockState::StateListNode mNode;

    virtual ~BlockState() = default;
    virtual void toNBT(CompoundTag&, int) const = 0;
    virtual bool fromNBT(const CompoundTag&, int&) const = 0;
};

struct BlockStateInstance {
    uint32_t mEndBit;
    uint32_t mNumBits;
    uint32_t mVariationCount;
    uint32_t mMask;
    bool mInitialized;
    const BlockState* mState;
};