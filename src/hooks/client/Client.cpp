#ifdef CLIENT
#include "hooks/client/Client.hpp"
#include "hooks/client/Input.hpp"
#include "hooks/client/Item.hpp"
#include "hooks/client/Rendering.hpp"
#include "hooks/client/Resource.hpp"
#include "hooks/client/UI.hpp"
#include "game/client/CustomUIRendererRegistry.hpp"

#include <amethyst/runtime/ModContext.hpp>
#include <amethyst/runtime/utility/InlineHook.hpp>
#include <amethyst/runtime/events/GameEvents.hpp>

#include <mc/src-client/common/client/game/ClientInstance.hpp>

using IMinecraftGame = MinecraftGame;
namespace Amethyst::ClientHooks {
	Amethyst::InlineHook<decltype(&ClientInstance::$constructor)> _ClientInstance_$constructor;
	ClientInstance* ClientInstance_$constructor(
		ClientInstance* self,
		IMinecraftGame& mg,
		IMinecraftApp& app,
		LevelListener& levelListener,
		SubClientId subid,
		const Bedrock::NotNullNonOwnerPtr<IAdvancedGraphicsOptions>& graphicsOptions,
		const Bedrock::NotNullNonOwnerPtr<ClientInstanceEventCoordinator>& coordinator,
		LatencyGraphDisplay* latencyGraphDisplay,
		const Bedrock::NotNullNonOwnerPtr<NetworkSessionOwner>& sessionOwner
	) {
		auto* result = _ClientInstance_$constructor(
			self, 
			mg, 
			app, 
			levelListener, 
			subid, 
			graphicsOptions, 
			coordinator, 
			latencyGraphDisplay, 
			sessionOwner
		);

		Amethyst::GetClientCtx().mClientInstance = self;
		return result;
	}

	Amethyst::InlineHook<decltype(&ClientInstance::onStartJoinGame)> _ClientInstance_onStartJoinGame;
	void* ClientInstance_onStartJoinGame(ClientInstance* self, bool unk0, const std::string& unk1, int unk2, Social::MultiplayerServiceIdentifier serviceId) {
		Amethyst::GetClientCtx().mIsInWorldOrLoading = true;
		OnStartJoinGameEvent event(*self);
		Amethyst::GetEventBus().Invoke(event);
		return _ClientInstance_onStartJoinGame(self, unk0, unk1, unk2, serviceId);
	}

	Amethyst::InlineHook<decltype(&ClientInstance::requestLeaveGame)> _ClientInstance_requestLeaveGame;
	void ClientInstance_requestLeaveGame(ClientInstance* self, bool switchScreen, bool sync) {
		Amethyst::GetClientCtx().mIsInWorldOrLoading = false;
		OnRequestLeaveGameEvent event(*self);
		Amethyst::GetEventBus().Invoke(event);
		_ClientInstance_requestLeaveGame(self, switchScreen, sync);
	}

	void Initialize() {
		auto& hooks = Amethyst::GetHookManager();
		HOOK(ClientInstance, $constructor);
		HOOK(ClientInstance, onStartJoinGame);
		HOOK(ClientInstance, requestLeaveGame);
		InputHooks::Initialize();
		ItemHooks::Initialize();
		RenderingHooks::Initialize();
		ResourceHooks::Initialize();
		UIHooks::Initialize();
		CustomUIRendererRegistry::AddEventListeners();
	}
}
#endif