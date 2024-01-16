#pragma once

#include <unordered_map>

#include "common/SharedPtr.h"
#include "common/world/item/Item.h"
#include "core/string/StringHash.h"

class ItemRegistry {
public:
    char padding0[0x28]; 
    std::unordered_map<int32_t, WeakPtr<Item>> mIdToItemMap; // this + 40
    std::unordered_map<HashedString, WeakPtr<Item>> mHashed;
};