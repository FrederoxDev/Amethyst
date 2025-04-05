#pragma once
#include "minecraft/src/common/world/item/ItemDescriptor.hpp"

class ItemDescriptorCount : public ItemDescriptor {
public:
    uint16_t mStackSize;

    ItemDescriptorCount operator=(const ItemDescriptorCount& other)
    {
        if (this != &other) {
            this->mStackSize = other.mStackSize;
            ItemDescriptor::operator=(other);
        }
        
        return *this;
    }
};