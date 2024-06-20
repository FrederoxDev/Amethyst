#pragma once
#include <minecraft/src/common/network/packet/Packet.hpp>
#include <minecraft/src/common/nbt/CompoundTagVariant.hpp>
#include <minecraft/src/common/nbt/CompoundTag.hpp>
#include <minecraft/src/common/network/NetworkBlockPosition.hpp>

class BlockActorDataPacket : public Packet {
public:
    NetworkBlockPosition mPos;
    CompoundTag mData;
};