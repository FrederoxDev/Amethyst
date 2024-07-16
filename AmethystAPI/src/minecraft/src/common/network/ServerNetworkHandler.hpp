#pragma once
#include <cstddef>
#include <minecraft/src-deps/core/utility/NonOwnerPointer.hpp>

class ILevel;
class NetworkIdentifier;
class LoginPacket;
class RequestNetworkSettingsPacket;

class ServerNetworkHandler {
public:
    std::byte padding0[88];
    Bedrock::NonOwnerPointer<ILevel> mLevel;

public:
    virtual void handle(const NetworkIdentifier&, const LoginPacket&);
    virtual void handle(const NetworkIdentifier&, const RequestNetworkSettingsPacket&);
};
