#ifdef CLIENT
#include "hooks/client/Client.hpp"
#include "hooks/client/Input.hpp"
#include "hooks/client/Rendering.hpp"
#include "hooks/client/Resource.hpp"
#include "hooks/client/UI.hpp"
#include "game/client/CustomUIRendererRegistry.hpp"

#include <amethyst/runtime/ModContext.hpp>
#include <amethyst/runtime/utility/InlineHook.hpp>
#include <amethyst/runtime/events/GameEvents.hpp>

#include <client/game/ClientInstance.hpp>
#include <client/Events/PlayerJoinWorldContext.hpp>

namespace Amethyst::ClientHooks {
	SafetyHookInline _ClientInstance_$constructor;
	ClientInstance* ClientInstance_$constructor(
		ClientInstance* self,
		ClientInstanceArguments&& args
	) {
		using OrigFn = ClientInstance* (*)(ClientInstance*, ClientInstanceArguments&&);
		auto* result = _ClientInstance_$constructor.original<OrigFn>()(self, std::move(args));

		Log::Info("ClientInstance constructed!");
		Amethyst::GetClientCtx().mClientInstance = self;
		return result;
	}

	Amethyst::InlineHook<decltype(&ClientInstance::onStartJoinGame)> _ClientInstance_onStartJoinGame;
	void ClientInstance_onStartJoinGame(ClientInstance* self, bool isJoiningLocalServer, const ::std::string& multiplayerCorrelationId, const ::std::string& serverName, const ::std::string& worldName, NetworkType networkTypeOverride, ::Social::MultiplayerServiceIdentifier service, PlayerJoinWorldContext context) {
		Amethyst::GetClientCtx().mIsInWorldOrLoading = true;
		OnStartJoinGameEvent event(*self);
		Amethyst::GetEventBus().Invoke(event);
		_ClientInstance_onStartJoinGame(self, isJoiningLocalServer, multiplayerCorrelationId, serverName, worldName, networkTypeOverride, service, std::move(context));
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
		VHOOK(ClientInstance, onStartJoinGame, ClientInstance::$vtable_for_ClientInstance$IClientInstance);
		VHOOK(ClientInstance, requestLeaveGame, ClientInstance::$vtable_for_ClientInstance$IClientInstance);
		// InputHooks::Initialize();
		RenderingHooks::Initialize();
		ResourceHooks::Initialize();
		// UIHooks::Initialize();
		// CustomUIRendererRegistry::AddEventListeners();
	}
}
#endif