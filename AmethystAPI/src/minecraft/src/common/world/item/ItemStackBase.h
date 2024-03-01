#pragma once
#include "amethyst/Memory.h"
#include "minecraft/src/common/SharedPtr.h"
#include <cstdint>
#include <string>

class Item;
class CompoundTag;

class ItemStackBase {
public:
    uintptr_t** vtable;
    WeakPtr<Item> mItem;    // this + 8
    CompoundTag* mUserData; // this + 16
    std::byte padding0[10];
    byte count; // this + 34;
    std::byte padding1[120];

public:
    // 1.20.51.1 - 48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 54 24 ? 57 48 83 EC ? 48 8B FA 48 8B E9 33 F6
    std::string getRawNameId() const;

    // 1.20.51.1 - 48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 48 8B F2 48 89 54 24 ? 4C 8B F9 48 89 4C 24
    void _loadItem(const CompoundTag*);
};