#pragma once

class ItemStackBase;

class ItemInstance : public ItemStackBase {

};

// ItemStackBase has ItemInstance as a member variable, so include has to be after declaration...
#include "minecraft/src/common/world/item/ItemStackBase.hpp"