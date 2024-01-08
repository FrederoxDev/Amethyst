#pragma once
#include "minecraft/src/common/world/Container.h"

// This is probably wrong in some way or outdated, from china
enum ContainerID : char {
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
    class SlotData {
    public:
        ContainerID mContainerId;
        int32_t mSlot;
    };

    bool padding0[16];
    int mSelected; // this + 16
    Container* container; // this + 24
    bool padding1[152];
    ContainerID mSelectedContainerId; // this + 184
};