#pragma once
#include <stdint.h>
#include <string>

#include "minecraft/common/world/item/ItemStackBase.h"
#include "minecraft/common/world/level/Level.h"

class Item {
private:
    uintptr_t** vtable;

public:
    // 40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 49 8B F1 4C 89 44 24 ? 4C 8B F2 48 8B D9
    typedef void(__thiscall* _appendFormattedHovertext)(Item*, const ItemStackBase&, Level&, std::string&, uint8_t);

    uint64_t getDamageValue(void*) const;
    uint64_t getMaxDamage() const;
};