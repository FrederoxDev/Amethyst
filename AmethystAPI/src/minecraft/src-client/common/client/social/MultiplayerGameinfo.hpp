#pragma once
#include <cstddef>
#include <minecraft/src-deps/core/file/Path.hpp>
#include <string>
#include <vector>

namespace Social {
enum GamePublishSetting : int32_t {
    NoMultiPlay = 0x0000,
    InviteOnly = 0x0001,
    FriendsOnly = 0x0002,
    FriendsOfFriends = 0x0003,
    Public = 0x0004,
};

enum ConnectionType : int16_t {
    Undefined = 0xff,
    Local = 0x0000,
    IPv4 = 0x0001,
    IPv6 = 0x0002,
    NAT = 0x0003,
    UPNP = 0x0004,
    UnknownIP = 0x0005,
};

enum MultiplayerServiceIdentifier : int32_t {
    XboxLive = 0x0000,
    Nintendo = 0x0001,
    AdHoc = 0x0002,
    Playstation = 0x0003,
    EDU = 0x0004,
    Mock = 0x0005,
    Invalid = 0xff,
};

class GameConnectionInfo {
public:
    ConnectionType mType;
    std::string mHostIpAddress;
    std::byte padding1[4];
    std::string mRakNetGUID;
    uint32_t mHostPort;
    std::byte padding2[20];
    uint64_t mNetherNetID;
};

class MultiplayerGameinfo {
public:
    std::byte padding1[16];
    std::vector<Social::GameConnectionInfo> mSupportedConnections;
    std::string mOwnerId;
    std::vector<uint64_t> mPlayerIds;
    std::string mOwnerNickname;
    std::string mHandleId;
    std::string mLevelId;
    std::string mSessionId;
    std::string mRakNetGUID;
    std::string mWorldName;
    std::string mWorldType;
    std::string mVersion;
    uint64_t mRealmId;
    std::string mThirdPartyServerId;
    std::string mThirdPartyServerIp;
    int32_t mThirdPartyServerPort;
    std::byte padding2[8];
    int64_t mGatheringId;
    std::byte padding3[8];
    std::byte padding4[32];
    std::string mOwnerPlayFabId;
    std::string mWorldName;
    int16_t mProtocol;
    int16_t mMaxMemberCount;
    int16_t mMemberCount;
    MultiplayerServiceIdentifier mServiceProvider;
    Core::Path mServiceIconPath;
    GamePublishSetting mBroadcastSetting;
    bool mLanGame;
    bool mOnlineCrossPlatformGame;
    std::byte padding5[2];
    int32_t mTransportLayer;
    std::byte padding6[4];
    int64_t mWebRTCNetworkId;
    int32_t mTitleId;
    bool mCrossPlayDisabled;
    bool mIsEditorWorld;
};
} // namespace Social