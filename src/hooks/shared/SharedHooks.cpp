#include "hooks/shared/SharedHooks.hpp"

#include <thread>

#include <amethyst/runtime/utility/InlineHook.hpp>
#include <amethyst/runtime/ModContext.hpp>
#include <amethyst/runtime/events/GameEvents.hpp>
#include <amethyst/runtime/events/RegisterEvents.hpp>

#include <mc/src-vanilla/vanilla_shared/common/server/module/VanillaGameModuleServer.hpp>
#include <mc/src-vanilla/vanilla_shared/common/resources/VanillaInPackagePacks.hpp>
#include <mc/src/common/world/level/block/definition/BlockDefinitionGroup.hpp>
#include <mc/src/common/world/level/block/registry/BlockTypeRegistry.hpp>
#include <mc/src/common/network/PacketHandlerDispatcherInstance.hpp>
#include <mc/src/common/world/item/registry/ItemRegistryRef.hpp>
#include <mc/src/common/network/ServerNetworkHandler.hpp>
#include <mc/src/common/world/item/VanillaItems.hpp>
#include <mc/src/common/network/packet/Packet.hpp>
#include <mc/src/common/world/level/Level.hpp>
#include <mc/src/common/Minecraft.hpp>

void RegisterCreativeItems(ItemRegistryRef ref, CreativeItemCategory category) {
	auto& sharedCtx = Amethyst::GetCurrentThreadCtx();
	auto& vanillaCategory = sharedCtx.mCreativeRegistry.GetVanillaCategory(CreativeItemCategory::Construction);
	vanillaCategory._RegisterItems(ref);
}

template <>
class PacketHandlerDispatcherInstance<Amethyst::CustomPacketInternal, false> : public IPacketHandlerDispatcher {
public:
	virtual void handle(const NetworkIdentifier& networkId, NetEventCallback& netEvent, std::shared_ptr<Packet>& _packet) const override {
		std::shared_ptr<Amethyst::CustomPacketInternal>& packet = (std::shared_ptr<Amethyst::CustomPacketInternal>&)_packet;
		Amethyst::CustomPacketHandler* handler = Amethyst::GetNetworkManager().GetPacketHandler(packet->mTypeId);

		if (handler == nullptr) {
			Log::Warning("[PacketHandlerDispatcherInstance] No handler found for CustomPacketInternal with typeId {}, ignoring packet", packet->mTypeId);
			return;
		}

		handler->handle(networkId, netEvent, *packet->mPacket.get());
	}
};

namespace Amethyst::SharedHooks {
	static PacketHandlerDispatcherInstance<Amethyst::CustomPacketInternal, false> AmethystCustomPacketHandler;
	void OnLevelEvent(Level* level) {
		if (level == nullptr) {
			OnLevelDestroyedEvent event;
			Amethyst::GetEventBus().Invoke(event);
			return;
		}

		OnLevelConstructedEvent event(*level);
		Amethyst::GetEventBus().Invoke(event);
	}

	#pragma region Minecraft
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
		if (!ctx.mPlatform->IsDedicatedServer() && Amethyst::GetClientCtx().mMinecraft == nullptr) {
			Amethyst::GetClientCtx().mMinecraft = result;
			ctx.mMainClientThread = std::this_thread::get_id();
		} else {
			Amethyst::GetContext().mServerCtx = std::make_unique<Amethyst::ServerContext>();
			Amethyst::GetServerCtx().mMinecraft = result;
			ctx.mMainServerThread = std::this_thread::get_id();
		}
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
	#pragma endregion
	#pragma region VanillaItems
	Amethyst::InlineHook<decltype(&VanillaItems::registerItems)> _VanillaItems_registerItems;
	void VanillaItems_registerItems(
		VanillaItems* self,
		const ItemRegistryRef itemRegistry,
		const BaseGameVersion& baseGameVersion,
		const Experiments& experiments
	) {
		_VanillaItems_registerItems(
			self, 
			itemRegistry, 
			baseGameVersion, 
			experiments
		);

		ItemRegistry* registry = itemRegistry.mItemRegistry.lock().get();
		auto& shared = Amethyst::GetCurrentThreadCtx();
		RegisterItemsEvent event(*registry, shared.mCreativeRegistry);
		Amethyst::GetEventBus().Invoke(event);
	}

	Amethyst::InlineHook<decltype(&VanillaItems::_addItemsCategory)> _VanillaItems__addItemsCategory;
	void VanillaItems__addItemsCategory(
		::CreativeItemRegistry* creative,
		ItemRegistryRef ref,
		const BaseGameVersion& version,
		const Experiments& experiments
	) {
		_VanillaItems__addItemsCategory(creative, ref, version, experiments);
		RegisterCreativeItems(ref, CreativeItemCategory::Items);
	}

	Amethyst::InlineHook<decltype(&VanillaItems::_addCommandOnlyCategory)> _VanillaItems__addCommandOnlyCategory;
	void VanillaItems__addCommandOnlyCategory(
		::CreativeItemRegistry* creative,
		ItemRegistryRef ref,
		const BaseGameVersion& version,
		const Experiments& experiments
	) {
		_VanillaItems__addCommandOnlyCategory(creative, ref, version, experiments);
		RegisterCreativeItems(ref, CreativeItemCategory::ItemCommandOnly);
	}
	
	Amethyst::InlineHook<decltype(&VanillaItems::_addEquipmentCategory)> _VanillaItems__addEquipmentCategory;
	void VanillaItems__addEquipmentCategory(
		::CreativeItemRegistry* creative,
		ItemRegistryRef ref,
		const BaseGameVersion& version,
		const Experiments& experiments
	) {
		_VanillaItems__addEquipmentCategory(creative, ref, version, experiments);
		RegisterCreativeItems(ref, CreativeItemCategory::Equipment);
	}
	
	Amethyst::InlineHook<decltype(&VanillaItems::_addNatureCategory)> _VanillaItems__addNatureCategory;
	void VanillaItems__addNatureCategory(
		::CreativeItemRegistry* creative,
		ItemRegistryRef ref,
		const BaseGameVersion& version,
		const Experiments& experiments
	) {
		_VanillaItems__addNatureCategory(creative, ref, version, experiments);
		RegisterCreativeItems(ref, CreativeItemCategory::Nature);
	}
	
	Amethyst::InlineHook<decltype(&VanillaItems::_addConstructionCategory)> _VanillaItems__addConstructionCategory;
	void VanillaItems__addConstructionCategory(
		::CreativeItemRegistry* creative,
		ItemRegistryRef ref,
		const BaseGameVersion& version,
		const Experiments& experiments
	) {
		_VanillaItems__addConstructionCategory(creative, ref, version, experiments);
		RegisterCreativeItems(ref, CreativeItemCategory::Construction);
	}
	#pragma endregion
	#pragma region BlockDefinitionGroup
	Amethyst::InlineHook<decltype(&BlockDefinitionGroup::registerBlocks)> _BlockDefinitionGroup_registerBlocks;
	void BlockDefinitionGroup_registerBlocks(BlockDefinitionGroup* self) {
		RegisterBlocksEvent event(*self);
		Amethyst::GetEventBus().Invoke(event);
		_BlockDefinitionGroup_registerBlocks(self);
	}
	#pragma endregion
	#pragma region VanillaGameModuleServer
	Amethyst::InlineHook<decltype(&VanillaGameModuleServer::initializeBehaviorStack)> _VanillaGameModuleServer_initializeBehaviorStack;
	void VanillaGameModuleServer_initializeBehaviorStack(
		VanillaGameModuleServer* self,
		const Experiments& experiments,
		const Bedrock::NotNullNonOwnerPtr<ResourcePackRepository>& repository,
		ResourcePackStack& stack,
		const BaseGameVersion& baseGameVer,
		GameModuleClient::ResourceLoadingPhase loadingPhase
	) {
		auto& context = Amethyst::GetContext();
		context.mPackManager->AddBehaviorPacksToStack(repository, stack);
		_VanillaGameModuleServer_initializeBehaviorStack(self, experiments, repository, stack, baseGameVer, loadingPhase);
	}
	#pragma endregion
	#pragma region ResourcePackRepository
	Amethyst::InlineHook<decltype(&ResourcePackRepository::_initializePackSource)> _ResourcePackRepository__initializePackSource;
	void ResourcePackRepository__initializePackSource(ResourcePackRepository* self) {
		_ResourcePackRepository__initializePackSource(self);
		auto& context = Amethyst::GetContext();
		auto& packManager = *context.mPackManager;
		const auto& allPacks = packManager.GetPacks();
		size_t totalSize = std::accumulate(
			allPacks.begin(), allPacks.end(), 0ull,
			[](size_t sum, const auto& pair) {
			return sum + pair.second.size();
		}
		);

		Log::Info("Initializing {} modded pack sources...", totalSize);

		// Add mod "resource_packs" and "behavior_packs" to the CompositePackSource
		for (auto& [nameVer, packs] : allPacks) {
			auto& platform = Amethyst::GetPlatform();
			fs::path modBasePath = platform.GetAmethystFolder() / "mods" / nameVer;

			// Check if the mod has resource packs
			bool hasResourcePacks = std::find_if(packs.begin(), packs.end(), [&](const auto& pair) {
				return pair.second.type == PackType::Resources;
			}) != packs.end();

			// Check if the mod has behavior packs
			bool hasBehaviorPacks = std::find_if(packs.begin(), packs.end(), [&](const auto& pair) {
				return pair.second.type == PackType::Behavior;
			}) != packs.end();

			// Add the resource pack source if it has resource packs
			if (hasResourcePacks) {
				auto& packSource = self->mPackSourceFactory.createDirectoryPackSource(Core::Path((modBasePath / "resource_packs").string()), PackType::Resources, PackOrigin::User, false);
				self->mPackSource->mPackSources.push_back(&packSource);
			}

			// Add the behavior pack source if it has behavior packs
			if (hasBehaviorPacks) {
				auto& packSource = self->mPackSourceFactory.createDirectoryPackSource(Core::Path((modBasePath / "behavior_packs").string()), PackType::Behavior, PackOrigin::User, false);
				self->mPackSource->mPackSources.push_back(&packSource);
			}
		}
	}
	#pragma endregion
	#pragma region ServerNetworkHandler
	Amethyst::InlineHook<decltype(&ServerNetworkHandler::allowIncomingPacketId)> _ServerNetworkHandler_allowIncomingPacketId;
	bool ServerNetworkHandler_allowIncomingPacketId(ServerNetworkHandler* self, const NetworkIdentifier& networkId, MinecraftPacketIds packet) {
		if ((int)packet == (int)MinecraftPacketIds::EndId + 1) {
			return true;
		}
		return _ServerNetworkHandler_allowIncomingPacketId(self, networkId, packet);
	}
	#pragma endregion
	#pragma region MinecraftPackets
	Amethyst::InlineHook<decltype(&MinecraftPackets::createPacket)> _MinecraftPackets_createPacket;
	std::shared_ptr<Packet> MinecraftPackets_createPacket(MinecraftPacketIds id) {
		// Vanilla packets.
		if (id <= MinecraftPacketIds::EndId) {
			std::shared_ptr<Packet> packet = _MinecraftPackets_createPacket(id);
			return packet;
		}
		// Custom packets
		if ((int)id == (int)MinecraftPacketIds::EndId + 1) {
			auto shared = std::make_shared<Amethyst::CustomPacketInternal>();
			shared->mHandler = &AmethystCustomPacketHandler;
			return shared;
		}
		AssertFail("MinecraftPackets::createPacket called with invalid packet id {}", (int)id);
	}
	#pragma endregion

	void Initialize() {
		auto& hooks = Amethyst::GetHookManager();
		HOOK(Minecraft, $constructor);
		HOOK(Minecraft, $destructor);
		HOOK(Minecraft, update);
		HOOK(VanillaItems, registerItems);
		HOOK(VanillaItems, _addItemsCategory);
		HOOK(VanillaItems, _addCommandOnlyCategory);
		HOOK(VanillaItems, _addEquipmentCategory);
		HOOK(VanillaItems, _addNatureCategory);
		HOOK(VanillaItems, _addConstructionCategory);
		HOOK(BlockDefinitionGroup, registerBlocks);
		VHOOK(VanillaGameModuleServer, initializeBehaviorStack, this);
		HOOK(ResourcePackRepository, _initializePackSource);
		HOOK(ServerNetworkHandler, allowIncomingPacketId);
		HOOK(MinecraftPackets, createPacket);
	}
}