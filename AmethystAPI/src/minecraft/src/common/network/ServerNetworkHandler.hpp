#pragma once
#include <cstddef>
#include <minecraft/src-deps/core/utility/NonOwnerPointer.hpp>

class ILevel;
class NetworkIdentifier;
class LoginPacket;
class RequestNetworkSettingsPacket;

class ServerNetworkHandler {
public:
    /* this + 8  */ std::byte padding8[80];
    /* this + 88 */ Bedrock::NonOwnerPointer<ILevel> mLevel;

public:
    virtual void handle(const NetworkIdentifier&, const LoginPacket&);
    virtual void handle(const NetworkIdentifier&, const RequestNetworkSettingsPacket&);
};

static_assert(offsetof(ServerNetworkHandler, mLevel) == 88);