#pragma once
#include <memory>
#include "minecraft/src/common/world/item/registry/ItemRegistry.h"

class ItemRegistryRef {
public:
    std::weak_ptr<ItemRegistry> mItemRegistry;
};