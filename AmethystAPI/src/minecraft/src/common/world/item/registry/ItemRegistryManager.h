#pragma once
#include "minecraft/src/common/world/item/registry/ItemRegistryRef.h"
#include "amethyst/Memory.h"

class ItemRegistryManager {
public:
    static ItemRegistryRef getItemRegistry();
};