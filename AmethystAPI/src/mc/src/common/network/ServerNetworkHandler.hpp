/// @symbols
#pragma once
#include <amethyst/Imports.hpp>
#include <mc/src/common/CommonTypes.hpp>

class NetworkIdentifier;
enum class MinecraftPacketIds;

class ServerNetworkHandler {
public:
	MC bool allowIncomingPacketId(const NetworkIdentifier& networkId, MinecraftPacketIds packet);
};
