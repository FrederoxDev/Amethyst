#pragma once
#include <minecraft/src-deps/core/utility/NonOwnerPointer.hpp>
#include <minecraft/src/common/network/ClientOrServerNetworkSystemRef.hpp>
#include <minecraft/src/common/gamerefs/OwnerPtr.hpp>
#include <minecraft/src/common/CommonTypes.hpp>

class EntityContext;
class Level;
class NetEventCallback;
class ServerNetworkHandler;
class LoopbackPacketSender;

struct GameSession {
    /* this + 0  */ ClientOrServerNetworkSystemRef mNetwork;
    /* this + 16 */ OwnerPtr<EntityContext> mLevelEntity;
    /* this + 32 */ Bedrock::NonOwnerPointer<Level> mLevel;
    /* this + 48 */ std::unique_ptr<ServerNetworkHandler> mServerNetworkHandler;
    /* this + 56 */ std::unique_ptr<NetEventCallback> mLegacyClientNetworkHandler;
    /* this + 64 */ std::unique_ptr<NetEventCallback> mClientNetworkHandler;
    /* this + 72 */ LoopbackPacketSender* mLoopbackPacketSender;
    /* this + 80 */ SubClientId mClientSubId;
};