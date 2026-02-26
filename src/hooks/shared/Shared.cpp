#include "hooks/shared/Shared.hpp"
#include "hooks/shared/Networking.hpp"
#include "hooks/shared/Resource.hpp"

#include <thread>

#include <amethyst/runtime/utility/InlineHook.hpp>
#include <amethyst/runtime/ModContext.hpp>
#include <amethyst/runtime/events/GameEvents.hpp>

#include <mc/src/common/world/level/Level.hpp>
#include <mc/src/common/Minecraft.hpp>

namespace Amethyst::SharedHooks {
	void OnLevelEvent(Level* level) {
		if (level == nullptr) {
			OnLevelDestroyedEvent event;
			Amethyst::GetEventBus().Invoke(event);
			return;
		}

		OnLevelConstructedEvent event(*level);
		Amethyst::GetEventBus().Invoke(event);
	}

	Amethyst::InlineHook<decltype(&Minecraft::$constructor)> _Minecraft_$constructor;
	Minecraft* Minecraft_$constructor(
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
	) {
		Minecraft* result = _Minecraft_$constructor(
			self,
			app,
			gameCallbacks,
			allowList,
			permissionsFile,
			filePathManager,
			maxPlayerIdleTime,
			eventing,
			network,
			packetSender,
			clientSubId,
			simTimer,
			realTimer,
			contentTierManager,
			serverMetrics
		);

		AmethystContext& ctx = Amethyst::GetContext();
		// This is where the initial threads ids are found, so at this point Amethsyt::IsOnMainClietnThread and Amethyst::IsOnMainServerThread will start working.
		// But for this it does have to do a tiny bit of jank such that this can be setup
#ifdef CLIENT
		if (!ctx.mPlatform->IsDedicatedServer() && Amethyst::GetClientCtx().mMinecraft == nullptr) {
			Amethyst::GetClientCtx().mMinecraft = result;
			ctx.mMainClientThread = std::this_thread::get_id();
		} else {
			Amethyst::GetContext().mServerCtx = std::make_unique<Amethyst::ServerContext>();
			Amethyst::GetServerCtx().mMinecraft = result;
			ctx.mMainServerThread = std::this_thread::get_id();
		}
#endif
#ifdef SERVER
		Amethyst::GetContext().mServerCtx = std::make_unique<Amethyst::ServerContext>();
		Amethyst::GetServerCtx().mMinecraft = result;
		ctx.mMainServerThread = std::this_thread::get_id();
#endif

		auto context = Bedrock::PubSub::SubscriptionContext::makeDefaultContext("Amethyst LevelEvent Subscriber");
		result->mLevelSubscribers->_connectInternal(OnLevelEvent, Bedrock::PubSub::ConnectPosition::AtFront, std::move(context), std::nullopt);
		return result;
	}

	Amethyst::InlineHook<decltype(&Minecraft::$destructor)> _Minecraft_$destructor;
	void Minecraft_$destructor(Minecraft* self, bool shouldDelete) {
		Amethyst::GetContext().mServerCtx.reset();
		_Minecraft_$destructor(self, shouldDelete);
	}

	Amethyst::InlineHook<decltype(&Minecraft::update)> _Minecraft_update;
	bool Minecraft_update(Minecraft* self) {
		bool value = _Minecraft_update(self);
		UpdateEvent event(*self);
		Amethyst::GetEventBus().Invoke(event);
		return value;
	}

	Amethyst::InlineHook<decltype(&Level::tick)> _Level_tick;
	void Level_tick(Level* self) {
		BeforeTickEvent event(*self);
		Amethyst::GetEventBus().Invoke(event);
		_Level_tick(self);
		AfterTickEvent afterEvent(*self);
		Amethyst::GetEventBus().Invoke(afterEvent);
	}

	void Initialize() {
		auto& hooks = Amethyst::GetHookManager();
		HOOK(Minecraft, $constructor);
		HOOK(Minecraft, $destructor);
		HOOK(Minecraft, update);
		VHOOK(Level, tick, this);
		NetworkingHooks::Initialize();
		ResourceHooks::Initialize();
	}
}