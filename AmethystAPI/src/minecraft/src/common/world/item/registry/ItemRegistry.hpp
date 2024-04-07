#pragma once
#include <unordered_map>
#include "minecraft/src/common/SharedPtr.hpp"
#include "minecraft/src/common/world/item/Item.hpp"
#include "minecraft/src-deps/core/string/StringHash.hpp"

class ItemRegistry {
public:
    std::byte padding0[0x28];
    std::unordered_map<int32_t, WeakPtr<Item>> mIdToItemMap; // this + 40
    std::unordered_map<HashedString, WeakPtr<Item>> mHashed;
    std::byte padding1[448];
    short mMaxItemID;

    template<typename T, typename... Args>
    WeakPtr<T> registerItemShared(Args&&... args) {
        SharedPtr<T> itemReg = SharedPtr<T>::make(std::forward<Args>(args)...);
        this->registerItem(itemReg);
        return itemReg;
    }

    // 1.20.51.1 - 48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 48 8B FA 4C 8B E9 48 89 55 ? 33 DB
    void registerItem(SharedPtr<Item> item);
};