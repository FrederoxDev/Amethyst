#pragma once
#include "minecraft/src/common/world/item/AuxDataBlockItem.h"

class ShulkerBoxBlockItem : public AuxDataBlockItem {
public:
    // 40 53 55 56 57 41 56 41 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 4D 8B F9 48 8B DA
    typedef void(__thiscall* _appendFormattedHovertext)(ShulkerBoxBlockItem*, const ItemStackBase&, Level&, std::string&, uint8_t);
};