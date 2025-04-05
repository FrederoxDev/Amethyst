#pragma once
#include <memory>
#include <minecraft/src/common/nbt/CompoundTagVariant.hpp>
#include <minecraft/src/common/nbt/CompoundTag.hpp>

//class CompoundTag;

class InventoryTransactionItemGroup {
public:
    int mItemId;
    int mItemAux;
    std::unique_ptr<CompoundTag> mTag;
    int mCount;
    bool mOverflow;
};