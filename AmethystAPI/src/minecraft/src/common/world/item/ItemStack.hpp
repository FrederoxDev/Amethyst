#pragma once
#include "minecraft/src/common/world/item/ItemStackBase.hpp"
#include "minecraft/src/common/world/inventory/network/ItemStackNetIdVariant.hpp"

class ItemStack : public ItemStackBase {
public:
    static ItemStack& EMPTY_ITEM;
    
public:
    ItemStackNetIdVariant mNetIdVariant;

public:
    ItemStack();
    ItemStack(const ItemStack& other) : ItemStackBase(other)
    {
        mNetIdVariant = other.mNetIdVariant;
    }
};

static_assert(sizeof(ItemStack) == 0xA0);