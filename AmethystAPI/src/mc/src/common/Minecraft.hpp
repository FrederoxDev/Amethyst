/// @symbols
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

	MC void $destructor(bool shouldDelete);

	MC bool update();
};
