#pragma once

#include "common/world/item/ItemStack.h"
#include "common/world/actor/player/Inventory.h"

// This is probably wrong in some way or outdated, from china
enum ContainerID : unsigned char {
    CONTAINER_ID_NONE = 0xff,
    CONTAINER_ID_INVENTORY = 0x0000,
    CONTAINER_ID_FIRST = 0x0001,
    CONTAINER_ID_LAST = 0x0064,
    CONTAINER_ID_OFFHAND = 0x0077,
    CONTAINER_ID_ARMOR = 0x0078,
    CONTAINER_ID_SELECTION_SLOTS = 0x007a,
    CONTAINER_ID_PLAYER_ONLY_UI = 0x007c,
};

class PlayerInventory {
public:
    class SlotData {
    public:
        ContainerID mContainerId;
        int32_t mSlot;
    };

public:
    uintptr_t** vtable0; // PlayerInventory::`vftable'{for `ContainerSizeChangeListener'}
    uintptr_t** vtable1; // PlayerInventory::`vftable'{for `ContainerContentChangeListener'}
    int32_t mSelected;
    ItemStack mInfiniteItem;
    ContainerID mSelectedContainerId;
    std::unique_ptr<Inventory> mInventory;
};