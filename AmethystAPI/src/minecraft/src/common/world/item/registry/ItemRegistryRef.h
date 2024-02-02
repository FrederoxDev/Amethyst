#pragma once
#include <memory>
#include "minecraft/src/common/world/item/registry/ItemRegistry.h"

class ItemRegistryRef {
public:
    std::weak_ptr<ItemRegistry> mItemRegistry;

    // 1.20.51.1 - 40 53 56 57 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 41 0F B7 F1
    template <typename Item>
    static WeakPtr<Item> registerItem(const HashedString* itemName, short legacyItemId) 
    {
        using function = WeakPtr<Item>(__thiscall*)(const HashedString*, short);
        static auto func = reinterpret_cast<function>(SigScan("40 53 56 57 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 41 0F B7 F1"));
        return func(itemName, legacyItemId);
    }
};
