#pragma once
#include "amethyst/Memory.h"
#include "minecraft/src/common/SharedPtr.h"
#include <stdint.h>
#include <string>

class Item;

class ItemStackBase {
private:
    uintptr_t** vtable;

public:
    WeakPtr<Item> mItem;
    void* mUserData;

    // 48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 54 24 ? 57 48 83 EC ? 48 8B FA 48 8B E9 33 F6
    typedef std::string&(__thiscall* _getRawNameId)(const ItemStackBase*, std::string&);
    std::string& getRawNameId(std::string&) const;
};