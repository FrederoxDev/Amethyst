#pragma once

#include "minecraft/src/common/SharedPtr.h"
#include <memory>
#include <minecraft/src/common/world/item/registry/ItemRegistryRef.h>

class BlockTypeRegistry;

class Level {
public:
    /* this + 0    */ std::byte padding0[840];
    /* this + 840  */ const ItemRegistryRef mItemRegistry;
    /* this + 856  */ std::byte padding856[8144];
};