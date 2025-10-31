/// @symbolgeneration
#pragma once
#include <cstddef>
#include <mc/src-deps/core/utility/NonOwnerPointer.hpp>
#include <mc/src/common/CommonTypes.hpp>
#include <mc/src/common/world/level/LevelListener.hpp>
#include <mc/src-deps/core/threading/EnableQueueForMainThread.hpp>
#include <mc/src/common/network/NetEventCallback.hpp>
#include <mc/src/common/network/packet/Packet.hpp>

class ServerPlayer;
class ILevel;
class NetworkIdentifier;
class LoginPacket;
class RequestNetworkSettingsPacket;

namespace Social {
class MultiplayerServiceObserver {
public:
    virtual ~MultiplayerServiceObserver() = default;
    virtual void padding0_eagfeg();
};

class XboxLiveUserObserver {
public:
    virtual ~XboxLiveUserObserver() = default;
    virtual void padding0_afdefe();
}; 
}

class ServerNetworkHandler : public Bedrock::Threading::EnableQueueForMainThread, public NetEventCallback, public LevelListener, public Social::MultiplayerServiceObserver, public Social::XboxLiveUserObserver {
public:
    /*  */ std::byte padding32[24];
    /* this + 88 */ Bedrock::NonOwnerPointer<ILevel> mLevel;

public:
    virtual ~ServerNetworkHandler();
    virtual void _unknown_0();
    // virtuals: cba to deal with virtual inheritance
    virtual ServerPlayer* _getServerPlayer(const NetworkIdentifier& source, SubClientId subId);

	/// @signature {48 89 5C 24 ? 48 89 6C 24 ? 56 57 41 56 48 83 EC ? 41 8B D8 48 8B F2, win-server}
    /// @signature {48 89 5C 24 ? 48 89 6C 24 ? 56 57 41 56 48 83 EC ? 41 8B D8 48 8B F2}
    MC bool allowIncomingPacketId(const NetworkIdentifier& networkId, MinecraftPacketIds packet);
};
 
static_assert(offsetof(ServerNetworkHandler, mLevel) == 88);