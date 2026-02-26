/// @symbols
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

class PlayerJoinWorldContext;
class ClientInstanceArguments {};

class ClientInstance {
public:
	MC static uintptr_t $vtable_for_this;

	/// @address {0x47060D0}
	MC static ClientInstance* $constructor(
		ClientInstance* self,
		ClientInstanceArguments& args
	);

	/** @address {0x470A520} */
	MC void onStartJoinGame(bool, const ::std::string&, const ::std::string&, const ::std::string&, int, int, PlayerJoinWorldContext*);

	/** @address {0x470AA20} */
	MC void requestLeaveGame(bool switchScreen, bool sync);
};
