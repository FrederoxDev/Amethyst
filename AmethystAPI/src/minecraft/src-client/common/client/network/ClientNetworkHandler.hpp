#pragma once
#include <cstddef>
#include <minecraft/src/common/network/NetEventCallback.hpp>
#include <minecraft/src-client/common/client/game/IClientInstance.hpp>

class Level;
class MinecraftCommands;
class IGameServerStartup;
class ClientNetworkSystem;
class PacketSender;
class PrivateKeyManager;
class IGameConnectionListener;

class ClientNetworkHandler : public NetEventCallback {
public:
    /* this + 24  */ std::byte padding24[48];
    /* this + 72  */ IClientInstance& mClient;
    /* this + 80  */ std::weak_ptr<IGameConnectionListener> mGameConnectionListener;
    /* this + 96  */ IGameServerStartup& mGameStartupServer;
    /* this + 104 */ ClientNetworkSystem& mClientNetworkSystem;
    /* this + 112 */ PacketSender& mPacketSender;
    /* this + 120 */ PrivateKeyManager& mPrivateKeyManager;
    /* this + 128 */ MinecraftCommands& mMinecraftCommands;
    /* this + 136 */ Level* mLevel;
};