#pragma once
#include "minecraft/common/world/item/registry/ItemRegistryRef.h"
#include "amethyst/Memory.h"

class ItemRegistryManager {
public:
    static ItemRegistryRef getItemRegistry();
};