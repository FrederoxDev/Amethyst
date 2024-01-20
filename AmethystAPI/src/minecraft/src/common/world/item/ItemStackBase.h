#pragma once
#include "amethyst/Memory.h"
#include "minecraft/src/common/SharedPtr.h"
#include <stdint.h>
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
    ItemStackBase() {};
    std::string& getRawNameId(std::string&) const;
    void _loadItem(const CompoundTag*);

//hooks:
    // 48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 54 24 ? 57 48 83 EC ? 48 8B FA 48 8B E9 33 F6
    typedef std::string&(__thiscall* _getRawNameId)(const ItemStackBase*, std::string&);
};