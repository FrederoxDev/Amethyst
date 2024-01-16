#pragma once
#include <memory>
#include "common/world/item/registry/ItemRegistry.h"

class ItemRegistryRef {
public:
    std::weak_ptr<ItemRegistry> mItemRegistry;
};