#pragma once
#include <minecraft/src/common/network/IPacketHandlerDispatcher.hpp>

template <typename Packet, bool Unk = false> 
class PacketHandlerDispatcherInstance : public IPacketHandlerDispatcher {
public:
    virtual void handle(const NetworkIdentifier&, NetEventCallback&, std::shared_ptr<Packet>) const;
};