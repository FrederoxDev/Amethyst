/// @symbolgeneration
#pragma once
#include <string>
#include <chrono>
#include <amethyst/Imports.hpp>
#include <mc/src/common/CommonTypes.hpp>
#include <mc/src-deps/core/utility/NonOwnerPointer.hpp>
#include <mc/src/common/network/ClientOrServerNetworkSystemRef.hpp>
#include <mc/src-deps/core/utility/pubsub/Publisher.hpp>
#include <mc/src-deps/core/utility/pubsub/ThreadModel.hpp>

class GameCallbacks;
class IMinecraftEventing;
class ResourcePackManager;
class AllowList;
class PermissionsFile;
class Timer;
class PacketSender;
class IMinecraftApp;
class Level;
class IContentTierManager;
class ServerMetrics;
namespace Core {
	class FilePathManager;
}

class Minecraft {
public:
	/* this + 0   */ std::byte padding0[288];
	/* this + 288 */ std::unique_ptr<Bedrock::PubSub::Publisher<void(Level*), Bedrock::PubSub::ThreadModel::SingleThreaded>> mLevelSubscribers;

	/// @signature {48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 4C 89 4C 24, win-server}
	/// @signature {48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 4D 8B E1 49 8B D8 4C 8B EA}
	MC static Minecraft* $constructor(
		Minecraft* self,
		IMinecraftApp& app,
		GameCallbacks& gameCallbacks,
		AllowList& allowList,
		PermissionsFile* permissionsFile,
		const Bedrock::NotNullNonOwnerPtr<Core::FilePathManager>& filePathManager,
		std::chrono::duration<int64_t> maxPlayerIdleTime,
		IMinecraftEventing& eventing,
		ClientOrServerNetworkSystemRef network,
		PacketSender& packetSender,
		SubClientId clientSubId,
		Timer& simTimer,
		Timer& realTimer,
		const Bedrock::NotNullNonOwnerPtr<const IContentTierManager>& contentTierManager,
		ServerMetrics* serverMetrics
	);

	/// @signature {48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B D9 48 8D 05 ? ? ? ? 48 89 01 48 8B 89, win-server}
	/// @signature {48 89 5C 24 ? 57 48 83 EC ? 8B DA 48 8B F9 E8 ? ? ? ? F6 C3 ? 74 ? BA ? ? ? ? 48 8B CF E8 ? ? ? ? 48 8B 5C 24 ? 48 8B C7 48 83 C4 ? 5F C3 CC CC CC CC CC CC CC CC CC CC CC CC 48 89 5C 24 ? 57 48 83 EC ? 48 8B D9 48 8D 05 ? ? ? ? 48 89 01 E8 ? ? ? ? 48 8B 8B}
	MC void $destructor(bool shouldDelete);

	/// @signature {48 8B C4 48 89 58 ? 48 89 70 ? 48 89 78 ? 55 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 8B E9 48 89 8D, win-server}
	/// @signature {48 8B C4 48 89 58 ? 48 89 70 ? 48 89 78 ? 55 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 8B E9 48 89 4C 24}
	MC bool update();
};
