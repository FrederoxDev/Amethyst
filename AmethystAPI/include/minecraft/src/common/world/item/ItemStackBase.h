#pragma once
#include "amethyst/Memory.h"

#include "minecraft/src/common/world/item/Item.h"
#include "minecraft/src/common/SharedPtr.h"

#include <stdint.h>
#include <string>

class CompoundTag;

class ItemStackBase {
private:
    uintptr_t** vtable;

public:
    WeakPtr<Item> mItem;    // this + 8
    CompoundTag* mUserData; // this + 16

    // 48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 54 24 ? 57 48 83 EC ? 48 8B FA 48 8B E9 33 F6
    typedef std::string&(__thiscall* _getRawNameId)(const ItemStackBase*, std::string&);
    std::string& getRawNameId(std::string&) const;
};