#include "minecraft/src/common/world/level/block/Block.hpp"
#include "minecraft/src/common/world/level/block/BlockLegacy.hpp"

template <typename T>
inline T Block::getState(const BlockState& blockState) const
{
    auto& states = mLegacyBlock->mStates;
    auto result = states.find(blockState.mID);

    if (blockState.mID >= result->first) {
        return (0xFFFF >> (16 - result->second.mNumBits)) & (mData >> (result->second.mEndBit - result->second.mNumBits + 1));
    }

    auto alteredState = mLegacyBlock->_tryLookupAlteredStateCollection(blockState.mID, mData);

    if (alteredState.has_value()) return alteredState.value();
    return 0;
}

template int Block::getState<int>(const BlockState& blockState) const;

template <typename T>
gsl::strict_not_null<const Block*> Block::setState(const BlockState& stateType, T value) const {
    auto& states = mLegacyBlock->mStates;
    auto foundState = states.find(stateType.mID);

    if (stateType.mID >= foundState->first) {
        if (value < (int64_t)foundState->second.mVariationCount) {
            uint64_t maskedData = mData & (~foundState->second.mMask);
            uint64_t index = maskedData | (value << (foundState->second.mEndBit - foundState->second.mNumBits + 1));

            if (index < mLegacyBlock->mBlockPermutations.size()) {
                return gsl::make_not_null(mLegacyBlock->mBlockPermutations[index].get());
            }
        }
        else {
            Log::Info("more than found variation count");
        }

        Assert("Not handling this ong!");
    }

    Assert("Unhandled case in Block::setState");
}

template gsl::strict_not_null<const Block*> Block::setState<int>(const BlockState& stateType, int value) const;

mce::Color Block::getMapColor(BlockSource& region, const BlockPos& pos) const
{
    return this->mLegacyBlock->getMapColor(region, pos, *this);
}