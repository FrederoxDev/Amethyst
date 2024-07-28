#pragma once
#include <minecraft/src/common/network/packet/Packet.hpp>

class ConnectionRequest;

class LoginPacket : public Packet {
public:
    uint32_t mClientNetworkVersion;
    std::unique_ptr<ConnectionRequest> mConnectionRequest;

    // 1.21.0.3 - 48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B F2 48 8B D9 8B 51
    virtual void write(BinaryStream&) override;

    // 1.21.0.3 - 40 55 53 56 57 41 56 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 49 8B F8 48 8B DA 48 8B F1 48 89 54 24 ? 45 33 F6 48 8D 55 ? 49 8B C8 E8 ? ? ? ? 48 8B D0 48 8D 4D ? E8 ? ? ? ? 90 44 38 75 ? 75 ? 48 8D 4D ? E8 ? ? ? ? 48 8D 4D ? E8 ? ? ? ? 80 BD ? ? ? ? ? 0F 85 ? ? ? ? 0F 10 05 ? ? ? ? 0F 11 45 ? 0F 10 0D ? ? ? ? 0F 11 4D ? C6 45 ? ? 48 8B 55 ? 48 3B 55 ? 74 ? 0F 11 02 0F 11 4A ? C6 42 ? ? 80 7D ? ? 74 ? 0F 57 C0 0F 11 42 ? 4C 89 72 ? 4C 89 72 ? 0F 10 45 ? 0F 11 42 ? 0F 10 4D ? 0F 11 4A ? 66 0F 6F 05 ? ? ? ? F3 0F 7F 45 ? C6 45 ? ? 48 8B 45 ? 48 89 42 ? 48 8B 45 ? 48 89 42 ? C6 42 ? ? 48 83 45 ? ? EB ? 4C 8D 45 ? 48 8D 4D ? E8 ? ? ? ? 80 7D ? ? 74 ? 48 8D 4D ? E8 ? ? ? ? 90 0F 28 45 ? 0F 11 85
    virtual Bedrock::Result<void, std::error_code> _read(ReadOnlyBinaryStream&) override;
};
