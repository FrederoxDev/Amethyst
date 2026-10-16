#include "hooks/shared/Shared.hpp"
#include "hooks/shared/Networking.hpp"
#include "hooks/shared/Resource.hpp"

#include <thread>

#include <amethyst/runtime/utility/InlineHook.hpp>
#include <amethyst/runtime/ModContext.hpp>
#include <amethyst/runtime/events/GameEvents.hpp>

#include <Debug/DebugUtils.hpp>
#include <world/Minecraft.hpp>

#ifdef CLIENT
#include <client/game/ClientInstance.hpp>
#endif

// #include <world/level/Level.hpp>

namespace Amethyst::SharedHooks {
	// Every thread the game starts for itself names itself here first, which makes this the
	// earliest point any of them can be told apart, and the only named one that the worker
	// pool threads pass through at all.
	Amethyst::InlineHook<decltype(&DebugUtils::setThreadName)> _DebugUtils_setThreadName;
	void DebugUtils_setThreadName(const std::string& name) {
		// ServerInstance::startServerThread names its thread MC_SERVER, and that thread is one
		// of only two callers of Minecraft::update, so the name identifies the server outright.
		Amethyst::ThreadClass threadClass = name == "MC_SERVER"
			? Amethyst::ThreadClass::MainServer
			: Amethyst::ThreadClass::EngineNamed;

		Amethyst::GetContext().mThreadRegistry.Record(std::this_thread::get_id(), threadClass, name);
		_DebugUtils_setThreadName(name);
	}

	// Minecraft::update has exactly two callers, ClientInstance::update and the thread body of
	// ServerInstance::startServerThread, so which Minecraft this is says which thread we are on.
	// ClientInstance::update calls it on its own mMinecraft, which is what the comparison uses.
	Amethyst::InlineHook<decltype(&Minecraft::update)> _Minecraft_update;
	bool Minecraft_update(Minecraft* self) {
		AmethystContext& ctx = Amethyst::GetContext();

#ifdef CLIENT
		ClientInstance* clientInstance = ctx.mClientCtx != nullptr ? ctx.mClientCtx->mClientInstance : nullptr;
		bool isClient = clientInstance != nullptr && clientInstance->mMinecraft.get() == self;
#else
		bool isClient = false;
#endif

		Amethyst::SharedContext* sideCtx = isClient
			? static_cast<Amethyst::SharedContext*>(ctx.mClientCtx.get())
			: static_cast<Amethyst::SharedContext*>(ctx.mServerCtx.get());

		if (sideCtx != nullptr)
			sideCtx->mMinecraft = self;

		ctx.mThreadRegistry.Record(
			std::this_thread::get_id(),
			isClient ? Amethyst::ThreadClass::MainClient : Amethyst::ThreadClass::MainServer,
			{});

		return _Minecraft_update(self);
	}

// 	void OnLevelEvent(Level* level) {
// 		if (level == nullptr) {
// 			OnLevelDestroyedEvent event;
// 			Amethyst::GetEventBus().Invoke(event);
// 			return;
// 		}

// 		OnLevelConstructedEvent event(*level);
// 		Amethyst::GetEventBus().Invoke(event);
// 	}

// 	Amethyst::InlineHook<decltype(&Level::tick)> _Level_tick;
// 	void Level_tick(Level* self) {
// 		BeforeTickEvent event(*self);
// 		Amethyst::GetEventBus().Invoke(event);
// 		_Level_tick(self);
// 		AfterTickEvent afterEvent(*self);
// 		Amethyst::GetEventBus().Invoke(afterEvent);
// 	}

	void Initialize() {
		auto& hooks = Amethyst::GetHookManager();

		// Addressed at runtime rather than through HOOK, because the address of an imported
		// free function is only settled once the import is resolved. Asking for it in the
		// constant expression HOOK needs yields this module's own import thunk, which the game
		// never calls, and the hook would take cleanly and then never fire.
		hooks.CreateHookAbsolute(
			_DebugUtils_setThreadName,
			reinterpret_cast<uintptr_t>(&DebugUtils::setThreadName),
			reinterpret_cast<void*>(&DebugUtils_setThreadName));

		HOOK(Minecraft, update);
		// HOOK(Level, tick);
		NetworkingHooks::Initialize();
		ResourceHooks::Initialize();
	}
}