#pragma once
#include <minecraft/src/common/world/Container.hpp>
#include <minecraft/src/common/world/item/ItemStack.hpp>

class SimpleContainer : public Container {
public:
    int mSize;
    std::vector<ItemStack> mItems;
    
    void serverInitItemStackIds(int, int, std::function<void(int, const ItemStack&)>) override {}
    
    const ItemStack& getItem(int slot) const override
    {
        if (slot < 0 || slot >= mItems.size())
            return ItemStack::EMPTY_ITEM;
        return mItems[slot];
    }
    
    void setItem(int slot, const ItemStack& item) override
    {
        if (slot < 0 || slot >= mItems.size())
            return;
        mItems[slot] = item;
    }
    
    int getContainerSize() const override
    {
        return static_cast<int>(mItems.size());
    }
    
    int getMaxStackSize() const override
    {
        return 64;
    }
    
    void startOpen(Player&) override {}
};