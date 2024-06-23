#pragma once
#include <memory>

class NetworkIdentifier;
class NetEventCallback;
class Packet;

class IPacketHandlerDispatcher {
public:
    virtual ~IPacketHandlerDispatcher() = default;
    virtual void handle(const NetworkIdentifier&, NetEventCallback&, std::shared_ptr<Packet>) const = 0;
};