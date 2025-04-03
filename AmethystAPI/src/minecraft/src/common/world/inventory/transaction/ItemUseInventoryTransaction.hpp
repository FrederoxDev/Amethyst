#pragma once
#include "minecraft/src/common/network/NetworkBlockPosition.hpp"
#include "minecraft/src/common/world/Facing.hpp"
#include "minecraft/src/common/world/inventory/transaction/ComplexInventoryTransaction.hpp"
#include "minecraft/src/common/world/level/block/Block.hpp"
#include "minecraft/src/common/world/phys/Vec3.hpp"

class ItemUseInventoryTransaction : public ComplexInventoryTransaction {
public:
    enum class ActionType {
        Place,
        Use,
        Destroy
    };

    ActionType mActionType;
    NetworkBlockPosition mPos;
    BlockRuntimeId mTargetBlockId;
    FacingID mFace;
    int32_t mSlot;
    NetworkItemStackDescriptor mItem;
    Vec3 mFromPos;
    Vec3 mClickPos;

public:
    ItemUseInventoryTransaction();

    void setTargetBlock(const Block& block)
    {
        this->mTargetBlockId = block.getRuntimeId();
    }
};

static_assert(sizeof(ItemUseInventoryTransaction) == 0x100);