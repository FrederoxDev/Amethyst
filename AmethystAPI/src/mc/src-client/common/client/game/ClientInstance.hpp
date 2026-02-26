/// @symbolgeneration
#pragma once
#include <string>
#include <amethyst/Imports.hpp>
#include <mc/src/common/CommonTypes.hpp>
#include <mc/src-deps/core/utility/NonOwnerPointer.hpp>

class MinecraftGame;
class IMinecraftApp;
class LevelListener;
class IAdvancedGraphicsOptions;
class ClientInstanceEventCoordinator;
class LatencyGraphDisplay;
class NetworkSessionOwner;
namespace Social {
	enum class MultiplayerServiceIdentifier;
}
using IMinecraftGame = MinecraftGame;

/** @vptr {48 8D 05 ? ? ? ? 48 89 06 48 8D 05 ? ? ? ? 48 89 46 ? 48 8D 05 ? ? ? ? 48 89 86} */
class ClientInstance {
public:
	MC static uintptr_t $vtable_for_this;

	/** @sig {48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 49 8B F9 49 8B D8 4C 8B E2} */
	MC static ClientInstance* $constructor(
		ClientInstance* self,
		IMinecraftGame& mg,
		IMinecraftApp& app,
		LevelListener& levelListener,
		SubClientId subid,
		const Bedrock::NotNullNonOwnerPtr<IAdvancedGraphicsOptions>& graphicsOptions,
		const Bedrock::NotNullNonOwnerPtr<ClientInstanceEventCoordinator>& coordinator,
		LatencyGraphDisplay* latencyGraphDisplay,
		const Bedrock::NotNullNonOwnerPtr<NetworkSessionOwner>& sessionOwner
	);

	/** @signature {40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 45 8B F1} */
	MC void* onStartJoinGame(bool unk0, const std::string& unk1, int unk2, Social::MultiplayerServiceIdentifier serviceId);

	/** @signature {48 89 5C 24 ? 48 89 74 24 ? 55 57 41 54 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 45 0F B6 F0 44 0F B6 FA} */
	MC void requestLeaveGame(bool switchScreen, bool sync);
};
