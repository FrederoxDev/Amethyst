#pragma once
#include <unordered_map>
#include "minecraft/common/SharedPtr.h"
#include "minecraft/common/world/item/Item.h"
#include "minecraft/common/core/string/StringHash.h"

class ItemRegistry {
public:
    char padding0[0x28]; 
    std::unordered_map<int32_t, WeakPtr<Item>> mIdToItemMap; // this + 40
    std::unordered_map<HashedString, WeakPtr<Item>> mHashed;
};