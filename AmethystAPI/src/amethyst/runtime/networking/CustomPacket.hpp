#pragma once

#include <memory>
#include <string>

#include <Core/Utility/BinaryStream.hpp>
#include <Platform/Result.hpp>
#include <network/NetworkPeer.hpp>
#include <raknet/PacketPriority.hpp>

class NetworkIdentifier;
class NetEventCallback;

namespace Amethyst {

class CustomPacket {
public:
    PacketPriority mPriority = PacketPriority::MEDIUM_PRIORITY;
    NetworkPeer::Reliability mReliability = NetworkPeer::Reliability::ReliableOrdered;
    Compressibility mCompressible = Compressibility::Compressible;

    CustomPacket() = default;
    virtual ~CustomPacket() = default;

    virtual std::string getName() const = 0;
    virtual void write(BinaryStream& out) const = 0;
    virtual Bedrock::Result<void, std::error_code> read(ReadOnlyBinaryStream& in) = 0;
};

class CustomPacketHandler {
public:
    virtual ~CustomPacketHandler() = default;
    virtual void handle(const NetworkIdentifier& source, NetEventCallback& callback, const CustomPacket& packet) const = 0;
};

} // namespace Amethyst
