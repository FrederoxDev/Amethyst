#pragma once
#include <string>
#include "minecraft/src/common/world/item/ItemDescriptorCount.hpp"
#include "minecraft/src/common/world/level/block/Block.hpp"
#include "minecraft/src/common/world/inventory/network/ItemStackNetIdVariant.hpp"

class NetworkItemStackDescriptor : ItemDescriptorCount {
	bool mIncludeNetIds;
	ItemStackNetIdVariant mNetIdVariant;
	BlockRuntimeId mBlockRuntimeId;
	std::string mUserDataBuffer;
};