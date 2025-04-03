#pragma once
#include "minecraft/src/common/world/inventory/transaction/InventorySource.hpp"
#include "minecraft/src/common/world/item/ItemStack.hpp"
#include "minecraft/src/common/world/inventory/network/NetworkItemStackDescriptor.hpp"

class InventoryAction {
public:
    InventorySource mSource;
    unsigned int mSlot;
    NetworkItemStackDescriptor mFromItemDescriptor;
    NetworkItemStackDescriptor mToItemDescriptor;
    ItemStack mFromItem;
    ItemStack mToItem;
};