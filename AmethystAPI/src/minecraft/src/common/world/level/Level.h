#pragma once

#include "minecraft/src/common/SharedPtr.h"
#include <memory>
#include <minecraft/src/common/world/item/registry/ItemRegistryRef.h>

class BlockTypeRegistry;

class Level {
public:
    /* this + 0    */ uintptr_t** vtable;
    /* this + 8    */ std::byte padding8[340];
    /* this + 348  */ const ItemRegistryRef mItemRegistry;
    /* this + 364  */ std::weak_ptr<BlockTypeRegistry> mBlockRegistry;
    /* this + 380  */ std::byte padding380[8620];
};