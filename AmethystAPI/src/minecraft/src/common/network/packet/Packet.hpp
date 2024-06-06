#pragma once
#include <cstdint>
#include <chrono>
#include <minecraft/src-deps/raknet/raknet/PacketPriority.hpp>
#include <minecraft/src/common/network/NetworkPeer.hpp>
#include <minecraft/src/common/CommonTypes.hpp>

class IPacketHandlerDispatcher;

class Packet {
public:
    uintptr_t** vtable;
    PacketPriority mPriority;
    NetworkPeer::Reliability mReliability;
    SubClientId mClientSubId;
    bool mIsHandled;
    std::chrono::steady_clock::time_point mReceiveTimepoint;
    const IPacketHandlerDispatcher* mHandler;
    Compressibility mCompressible;
};