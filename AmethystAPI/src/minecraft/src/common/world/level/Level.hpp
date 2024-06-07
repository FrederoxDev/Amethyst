#pragma once

#include "minecraft/src/common/SharedPtr.hpp"
#include <memory>
#include <minecraft/src/common/world/item/registry/ItemRegistryRef.hpp>

class BlockTypeRegistry;
class PacketSender;

class Level {
public:
    /* this + 0    */ std::byte padding0[840];
    /* this + 840  */ const ItemRegistryRef mItemRegistry;
    /* this + 856  */ std::byte padding856[1976];
    /* this + 2832 */ PacketSender* mPacketSender;
    /* this + 2840 */ std::byte padding2840[2761];
    /* this + 5601 */ bool isClientSide;
};