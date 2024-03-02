#pragma once
#include "minecraft/src/common/world/item/ItemStackBase.h"
#include "amethyst/Memory.h"

class ItemStackNetIdVariant {
    std::byte padding0[24];
};

static_assert(sizeof(ItemStackNetIdVariant) == 24);

class ItemStack : public ItemStackBase {
public:
    ItemStackNetIdVariant mNetIdVariant;

public:
    ItemStack();
};

static_assert(sizeof(ItemStack) == 0xA0);