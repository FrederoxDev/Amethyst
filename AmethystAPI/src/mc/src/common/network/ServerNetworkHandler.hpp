/// @symbolgeneration
#pragma once
#include <amethyst/Imports.hpp>
#include <mc/src/common/CommonTypes.hpp>

class NetworkIdentifier;
enum class MinecraftPacketIds;

class ServerNetworkHandler {
public:
	/// @signature {48 89 5C 24 ? 48 89 6C 24 ? 56 57 41 56 48 83 EC ? 41 8B D8 48 8B F2, win-server}
	/// @signature {48 89 5C 24 ? 48 89 6C 24 ? 56 57 41 56 48 83 EC ? 41 8B D8 48 8B F2}
	MC bool allowIncomingPacketId(const NetworkIdentifier& networkId, MinecraftPacketIds packet);
};
