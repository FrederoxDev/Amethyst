#pragma once
#include "minecraft/src/common/world/item/Item.hpp"

class BlockItem : public Item {
public:
    virtual bool isDestructive(int) const override;
    virtual bool isValidAuxValue(int value) const override;
    virtual std::string buildDescriptionId(const ItemDescriptor&, const CompoundTag*) const override;
    virtual ResolvedItemIconInfo getIconInfo(const ItemStackBase&, int, bool) const override;
    virtual Brightness getLightEmission(int) const override;
    virtual int getIconYOffset() const override;
protected:
    virtual bool _calculatePlacePos(ItemStackBase&, Actor&, unsigned char&, BlockPos&) const override;
    virtual InteractionResult _useOn(ItemStack&, Actor&, BlockPos, unsigned char, const Vec3&) const override;
public:
    BlockItem(const std::string& nameId, short mId);
};