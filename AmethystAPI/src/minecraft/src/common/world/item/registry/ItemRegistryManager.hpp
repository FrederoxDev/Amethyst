#pragma once
#include "minecraft/src/common/world/item/registry/ItemRegistryRef.hpp"
#include "amethyst/Memory.hpp"

class ItemRegistryManager {
public:
    static ItemRegistryRef getItemRegistry();
};