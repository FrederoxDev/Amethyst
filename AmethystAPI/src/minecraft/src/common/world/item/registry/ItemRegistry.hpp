#pragma once
#include <unordered_map>
#include "minecraft/src/common/SharedPtr.hpp"
#include "minecraft/src/common/world/item/Item.hpp"
#include "minecraft/src-deps/core/string/StringHash.hpp"

class ItemRegistry {
public:
    /* this + 0   */ std::byte padding0[0x28];
    /* this + 40  */ std::unordered_map<int32_t, WeakPtr<Item>> mIdToItemMap;
    /* this + 104 */ std::unordered_map<HashedString, WeakPtr<Item>> mNameToItemMap;
    /* this + 168 */ std::byte padding168[448];
    /* this + 616 */ short mMaxItemID;

    template<typename T, typename... Args>
    WeakPtr<T> registerItemShared(Args&&... args) {
        SharedPtr<T> itemReg = SharedPtr<T>::make(std::forward<Args>(args)...);
        registerItem(itemReg);
        return itemReg;
    }

    // 1.20.71.1 - 48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 8B EA 4C 8B F1 48 89 4C 24 ? 48 89 55      
    void registerItem(SharedPtr<Item> item);
};