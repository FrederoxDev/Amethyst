// #pragma once
// #include <string>
// #include <memory>
// #include <common/network/NetworkPeer.hpp>
// #include <Platform/Result.hpp>
// #include <Core/Utility/BinaryStream.hpp>
// #include <common/network/Packet.hpp>

// class NetworkIdentifier;
// class NetEventCallback;

// namespace Amethyst {

// class CustomPacket {
// public:
//     PacketPriority mPriority;
//     NetworkPeer::Reliability mReliability;
//     Compressibility mCompressible;

//     CustomPacket()
//         : mPriority(PacketPriority::MEDIUM_PRIORITY), mReliability(NetworkPeer::Reliability::ReliableOrdered), mCompressible(Compressibility::Compressible) {}

//     virtual std::string getName() const = 0;
//     virtual void write(BinaryStream& out) = 0;
//     virtual Bedrock::Result<void, std::error_code> read(ReadOnlyBinaryStream& in) = 0;
// };

// class CustomPacketHandler {
// public:
//     virtual void handle(const NetworkIdentifier& networkId, NetEventCallback& callback, const Amethyst::CustomPacket& _packet) const = 0;
// };

// }