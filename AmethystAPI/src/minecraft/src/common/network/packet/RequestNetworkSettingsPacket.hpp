#pragma once
#include <minecraft/src/common/network/packet/Packet.hpp>

class RequestNetworkSettingsPacket : public Packet {
public:
    uint32_t mClientNetworkVersion;

    virtual void write(BinaryStream&) override;
    virtual Bedrock::Result<void, std::error_code> _read(ReadOnlyBinaryStream&) override;
};
