#pragma once
#include <memory>

class CompoundTag;

class InventoryTransactionItemGroup {
public:
    int mItemId;
    int mItemAux;
    std::unique_ptr<CompoundTag> mTag;
    int mCount;
    bool mOverflow;
};