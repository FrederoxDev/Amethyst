#pragma once
#include "minecraft/src/common/world/item/ItemStackBase.hpp"
#include "amethyst/Memory.hpp"
#include "minecraft/src/common/world/inventory/network/ItemStackNetIdVariant.hpp"

class ItemStack : public ItemStackBase {
public:
    ItemStackNetIdVariant mNetIdVariant;

public:
    ItemStack();
};

static_assert(sizeof(ItemStack) == 0xA0);