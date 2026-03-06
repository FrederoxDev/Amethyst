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

#include <common/client/game/ClientInstance.hpp>

namespace Amethyst::ClientHooks {
	// Amethyst::InlineHook<decltype(&ClientInstance::$constructor)> _ClientInstance_$constructor;
	// ClientInstance* ClientInstance_$constructor(
	// 	ClientInstance* self,
	// 	ClientInstanceArguments& args
	// ) {
	// 	auto* result = _ClientInstance_$constructor(
	// 		self, 
	// 		args
	// 	);

	// 	Amethyst::GetClientCtx().mClientInstance = self;
	// 	return result;
	// }

	// Amethyst::InlineHook<decltype(&ClientInstance::onStartJoinGame)> _ClientInstance_onStartJoinGame;
	// void ClientInstance_onStartJoinGame(ClientInstance* self, bool a1, const ::std::string& a2, const ::std::string& a3, const ::std::string& a4, int a5, int a6, PlayerJoinWorldContext* a7) {
	// 	Amethyst::GetClientCtx().mIsInWorldOrLoading = true;
	// 	OnStartJoinGameEvent event(*self);
	// 	Amethyst::GetEventBus().Invoke(event);
	// 	_ClientInstance_onStartJoinGame(self, a1, a2, a3, a4, a5, a6, a7);
	// }

	// Amethyst::InlineHook<decltype(&ClientInstance::requestLeaveGame)> _ClientInstance_requestLeaveGame;
	// void ClientInstance_requestLeaveGame(ClientInstance* self, bool switchScreen, bool sync) {
	// 	Amethyst::GetClientCtx().mIsInWorldOrLoading = false;
	// 	OnRequestLeaveGameEvent event(*self);
	// 	Amethyst::GetEventBus().Invoke(event);
	// 	_ClientInstance_requestLeaveGame(self, switchScreen, sync);
	// }

	void Initialize() {
		auto& hooks = Amethyst::GetHookManager();
		// HOOK(ClientInstance, $constructor);
		// HOOK(ClientInstance, onStartJoinGame);
		// HOOK(ClientInstance, requestLeaveGame);
		// InputHooks::Initialize();
		// RenderingHooks::Initialize();
		// ResourceHooks::Initialize();
		// UIHooks::Initialize();
		// CustomUIRendererRegistry::AddEventListeners();
	}
}
#endif