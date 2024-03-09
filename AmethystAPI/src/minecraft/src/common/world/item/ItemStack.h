#pragma once
#include "minecraft/src/common/world/item/ItemStackBase.h"
#include "amethyst/Memory.h"
#include "minecraft/src/common/world/inventory/network/ItemStackNetIdVariant.h"

class ItemStack : public ItemStackBase {
public:
    ItemStackNetIdVariant mNetIdVariant;

public:
    ItemStack();
};

static_assert(sizeof(ItemStack) == 0xA0);