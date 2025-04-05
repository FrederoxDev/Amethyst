#pragma once
#include <string>
#include "minecraft/src/common/world/item/ItemDescriptorCount.hpp"
#include "minecraft/src/common/CommonTypes.hpp"
#include "minecraft/src/common/world/inventory/network/ItemStackNetIdVariant.hpp"

class ItemStack;

class NetworkItemStackDescriptor : public ItemDescriptorCount {
public:
	bool mIncludeNetIds;
	ItemStackNetIdVariant mNetIdVariant;
	BlockRuntimeId mBlockRuntimeId;
	std::string mUserDataBuffer;

	NetworkItemStackDescriptor(const ItemStack& stack);

	NetworkItemStackDescriptor operator=(const NetworkItemStackDescriptor& other) {
        if (this != &other) {
            ItemDescriptorCount::operator=(other);
            this->mIncludeNetIds = other.mIncludeNetIds;
            this->mNetIdVariant = other.mNetIdVariant;
            this->mBlockRuntimeId = other.mBlockRuntimeId;
            this->mUserDataBuffer = other.mUserDataBuffer;
		}
            
        return *this;
	}
};