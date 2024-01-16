#pragma once
#include <memory>
#include "minecraft/common/world/item/registry/ItemRegistry.h"

class ItemRegistryRef {
public:
    std::weak_ptr<ItemRegistry> mItemRegistry;
};