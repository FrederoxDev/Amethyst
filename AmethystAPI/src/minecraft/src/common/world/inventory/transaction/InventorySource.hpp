#pragma once
#include "minecraft/src/common/world/actor/player/PlayerInventory.hpp"

enum class InventorySourceType : int32_t {
    InvalidInventory = 0xFFFFFFFF,
    ContainerInventory = 0x0,
    GlobalInventory = 0x1,
    WorldInteraction = 0x2,
    CreativeInventory = 0x3,
    NonImplementedFeatureTODO = 0x1869F,
};

class InventorySource {
public:
    enum class InventorySourceFlags {
        NoFlag = 0x0,
        WorldInteraction_Random = 0x1,
    };

    InventorySourceType mType;
	ContainerID mContainerId;
	InventorySourceFlags mFlags;

    InventorySource(InventorySourceType type, ContainerID container, InventorySourceFlags flags) : 
        mType(type), mContainerId(container), mFlags(flags) {}

    InventorySource(const InventorySource& other) {
        this->mType = other.mType;
        this->mContainerId = other.mContainerId;
        this->mFlags = other.mFlags;
    }
};