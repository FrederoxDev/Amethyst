#pragma once

class ItemStackBase;

class ItemInstance : public ItemStackBase {
public:
    ItemInstance(const ItemStackBase& base) : ItemStackBase(base) {
        vtable = (uintptr_t**)AddressFromLeaInstruction(SigScan("48 8D 05 ? ? ? ? 49 89 06 48 8D 15"));
    }
};

// ItemStackBase has ItemInstance as a member variable, so include has to be after declaration...
#include "minecraft/src/common/world/item/ItemStackBase.hpp"