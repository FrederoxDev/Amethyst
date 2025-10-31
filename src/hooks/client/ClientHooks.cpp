#ifdef CLIENT
#include "hooks/client/ClientHooks.hpp"

#include <amethyst/runtime/ModContext.hpp>
#include <amethyst/runtime/utility/InlineHook.hpp>
#include <amethyst/runtime/events/RenderingEvents.hpp>
#include <amethyst/runtime/events/RegisterEvents.hpp>
#include <amethyst/runtime/events/GameEvents.hpp>
#include <amethyst/runtime/events/InputEvents.hpp>
#include <amethyst/runtime/events/UiEvents.hpp>

#include <mc/src-deps/input/MouseDevice.hpp>
#include <mc/src-client/common/client/game/ClientInstance.hpp>
#include <mc/src-client/common/client/gui/ScreenView.hpp>
#include <mc/src-client/common/client/renderer/block/BlockGraphics.hpp>
#include <mc/src-client/common/client/renderer/screen/MinecraftUIRenderContext.hpp>
#include <mc/src-client/common/client/input/VanillaClientInputMappingFactory.hpp>
#include <mc/src-client/common/client/renderer/blockActor/BlockActorRendererDispatcher.hpp>
#include <mc/src-client/common/client/renderer/game/LevelRenderer.hpp>
#include <mc/src-client/common/client/gui/screens/ScreenController.hpp>
#include <mc/src-client/common/client/gui/screens/ScreenEvent.hpp>
#include <mc/src-client/common/client/gui/screens/controllers/StartMenuScreenController.hpp>
#include <mc/src-vanilla/vanilla_client/common/module/VanillaGameModuleClient.hpp>
#include <mc/src/common/locale/I18n.hpp>

bool ShowAdvancedItemInfo = false;
namespace Amethyst::ClientHooks {
	#pragma region ScreenView
	Amethyst::InlineHook<decltype(&ScreenView::setupAndRender)> _ScreenView_setupAndRender;
	void ScreenView_setupAndRender(ScreenView* self, MinecraftUIRenderContext& ctx) {
		auto& bus = Amethyst::GetEventBus();
		BeforeRenderUIEvent ev(*self, ctx);
		bus.Invoke(ev);
		_ScreenView_setupAndRender(self, ctx);
		AfterRenderUIEvent afterEv(*self, ctx);
		bus.Invoke(afterEv);
	}
	#pragma endregion
	#pragma region ClientInstance
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
	#pragma endregion
	#pragma region BlockGraphics
	Amethyst::InlineHook<decltype(&BlockGraphics::initBlocks)> _BlockGraphics_initBlocks;
	void BlockGraphics_initBlocks(ResourcePackManager& resources, const Experiments& experiments) {
		_BlockGraphics_initBlocks(resources, experiments);
		InitBlockGraphicsEvent event(resources, experiments);
		Amethyst::GetEventBus().Invoke(event);
	}
	#pragma endregion
	#pragma region BlockActorRenderDispatcher
	Amethyst::InlineHook<decltype(&BlockActorRenderDispatcher::initializeBlockEntityRenderers)> _BlockActorRenderDispatcher_initializeBlockEntityRenderers;
	void BlockActorRenderDispatcher_initializeBlockEntityRenderers(
		BlockActorRenderDispatcher* self,
		const Bedrock::NotNullNonOwnerPtr<GeometryGroup>& geometryGroup,
		std::shared_ptr<mce::TextureGroup> textures,
		BlockTessellator& blockTessellator,
		const Bedrock::NotNullNonOwnerPtr<const ActorResourceDefinitionGroup>& entityResourceDefGroup,
		ResourcePackManager& resourcePackManager,
		MinecraftGameplayGraphicsResources& gameplayGraphicsResources,
		Bedrock::NotNullNonOwnerPtr<ResourceLoadManager> resourceLoadManager,
		const BaseGameVersion& version,
		const Experiments& experiments
	) {
		_BlockActorRenderDispatcher_initializeBlockEntityRenderers(
			self,
			geometryGroup,
			textures,
			blockTessellator,
			entityResourceDefGroup,
			resourcePackManager,
			gameplayGraphicsResources,
			resourceLoadManager,
			version,
			experiments
		);

		InitBlockEntityRenderersEvent event(*self, geometryGroup, textures, blockTessellator, entityResourceDefGroup, resourcePackManager, gameplayGraphicsResources, resourceLoadManager, version, experiments);
		Amethyst::GetEventBus().Invoke(event);
	}
	#pragma endregion
	#pragma region VanillaClientInputMappingFactory
	Amethyst::InlineHook<decltype(&VanillaClientInputMappingFactory::_addFullKeyboardGamePlayControls)> _VanillaClientInputMappingFactory__addFullKeyboardGamePlayControls;
	void VanillaClientInputMappingFactory__addFullKeyboardGamePlayControls(
		VanillaClientInputMappingFactory* self,
		KeyboardInputMapping* keyboard,
		MouseInputMapping* mouse
	) {
		_VanillaClientInputMappingFactory__addFullKeyboardGamePlayControls(self, keyboard, mouse);
		Amethyst::InputManager* inputManager = Amethyst::GetContext().mInputManager.get();
		inputManager->_registerKeyboardInputs(self, keyboard, mouse, Amethyst::KeybindContext::Gameplay);
	}

	Amethyst::InlineHook<decltype(&VanillaClientInputMappingFactory::_createScreenKeyboardAndMouseMapping)> _VanillaClientInputMappingFactory__createScreenKeyboardAndMouseMapping;
	void VanillaClientInputMappingFactory__createScreenKeyboardAndMouseMapping(
		VanillaClientInputMappingFactory* self,
		KeyboardInputMapping& keyboard,
		MouseInputMapping& mouse
	) {
		_VanillaClientInputMappingFactory__createScreenKeyboardAndMouseMapping(self, keyboard, mouse);
		Amethyst::InputManager* inputManager = Amethyst::GetContext().mInputManager.get();
		inputManager->_registerKeyboardInputs(self, &keyboard, &mouse, Amethyst::KeybindContext::Screen);
	}

	Amethyst::InlineHook<decltype(&VanillaClientInputMappingFactory::createInputMappingTemplates)> _VanillaClientInputMappingFactory_createInputMappingTemplates;
	void VanillaClientInputMappingFactory_createInputMappingTemplates(VanillaClientInputMappingFactory* self, Options* opt) {
		_VanillaClientInputMappingFactory_createInputMappingTemplates(self, opt);

		// This options is cached for later times the runtime needs to add keybinds.
		// This function createInputMappingTemplates is called once at the very start of the game and never again.
		Amethyst::GetClientCtx().mOptions = opt;

		// Since this is the first time, register all custom keybinds now that options is available.
		RegisterInputsEvent event(*Amethyst::GetContext().mInputManager.get());
		Amethyst::GetEventBus().Invoke(event);
	}
	#pragma endregion
	#pragma region MouseDevice
	Amethyst::InlineHook<decltype(&MouseDevice::feed)> _MouseDevice_feed;
	void MouseDevice_feed(
		MouseDevice* self,
		char actionButtonId,
		char buttonData,
		short x,
		short y,
		short dx,
		short dy,
		bool forceMotionlessPointer
	) {
		MouseInputEvent event(actionButtonId, buttonData, x, y, dx, dy);
		Amethyst::GetEventBus().Invoke(event);
		if (!event.IsCanceled()) {
			_MouseDevice_feed(self, actionButtonId, buttonData, x, y, dx, dy, forceMotionlessPointer);
		}
	}
	#pragma endregion
	#pragma region InputHandler
	Amethyst::InlineHook<decltype(&InputHandler::handleButtonEvent)> _InputHandler_handleButtonEvent;
	void InputHandler_handleButtonEvent(
		InputHandler* self,
		const ButtonEventData& button,
		FocusImpact focus,
		IClientInstance& client,
		int controllerId
	) {
		Amethyst::InputPassthrough passthrough = Amethyst::GetContext().mInputManager->_handleButtonEvent(self, button, focus, client, controllerId);
		if (passthrough == Amethyst::InputPassthrough::Passthrough) {
			_InputHandler_handleButtonEvent(self, button, focus, client, controllerId);
		}
	}
	#pragma endregion
	#pragma region LevelRenderer
	Amethyst::InlineHook<decltype(&LevelRenderer::renderLevel)> _LevelRenderer_renderLevel;
	void LevelRenderer_renderLevel(LevelRenderer* self, ScreenContext& screenContext, FrameRenderObject& frameRenderObj) {
		Amethyst::EventBus& bus = Amethyst::GetEventBus();
		BeforeRenderLevelEvent beforeEvent(*self, screenContext, frameRenderObj);
		bus.Invoke(beforeEvent);
		_LevelRenderer_renderLevel(self, screenContext, frameRenderObj);
		AfterRenderLevelEvent afterEvent(*self, screenContext, frameRenderObj);
		bus.Invoke(afterEvent);
	}
	#pragma endregion
	#pragma region ScreenController
	Amethyst::InlineHook<decltype(&ScreenController::_handleButtonEvent)> _ScreenController__handleButtonEvent;
	ui::ViewRequest ScreenController__handleButtonEvent(ScreenController* screen, ScreenEvent& event) {
		ui::ViewRequest result = _ScreenController__handleButtonEvent(screen, event);
		UIButtonHandleEvent ev(event);
		Amethyst::GetEventBus().Invoke(ev);
		return result;
	}
	#pragma endregion
	#pragma region StartMenuScreenController
	Amethyst::InlineHook<decltype(&StartMenuScreenController::_registerBindings)> _StartMenuScreenController__registerBindings;
	void StartMenuScreenController__registerBindings(StartMenuScreenController* self) {
		_StartMenuScreenController__registerBindings(self);
		auto& context = Amethyst::GetContext();
		const Amethyst::Mod* ownMod = Amethyst::GetOwnMod();
		std::string versionStr;
		if (ownMod->mInfo->Version.prerelease_tag() == "dev")
			versionStr = std::format("{}", "§uAmethyst Runtime (DEV)§r");
		else
			versionStr = std::format("Amethyst Runtime v{}", ownMod->mInfo->Version.to_string());

		// Register '#amethyst_version' binding
		self->bindString(StringHash("#amethyst_version"), [versionStr]() {
			return versionStr;
		}, []() {
			return true;
		});

		// Register '#mods_loaded' binding
		self->bindString(StringHash("#mods_loaded"), [&context]() -> std::string {
			// Not beautiful but works
			auto* mod = GetOwnMod();
			if (!mod)
				return "Reloading...";

			auto* importer = mod->GetImporter();
			if (!importer || !importer->IsResolved() || !context.mModLoader) {
				return "Reloading...";
			}

			size_t count = context.mModLoader->GetModCount();
			std::string modsLoadedLocalized = "text.amethyst.mods_loaded"_i18n;
			bool plural = (count != 1);
			std::string pluralSuffix = plural ? "s" : "";
			return std::vformat(modsLoadedLocalized, std::make_format_args(count, pluralSuffix, pluralSuffix));
		}, []() {
			return true;
		});
	}
	#pragma endregion
	#pragma region VanillaGameModuleClient
	Amethyst::InlineHook<decltype(&VanillaGameModuleClient::initializeResourceStack)> _VanillaGameModuleClient_initializeResourceStack;
	void VanillaGameModuleClient_initializeResourceStack(
		VanillaGameModuleClient* self,
		const Experiments& experiments,
		const Bedrock::NotNullNonOwnerPtr<ResourcePackRepository>& repository,
		ResourcePackStack& stack,
		const BaseGameVersion& baseGameVer,
		GameModuleClient::ResourceLoadingPhase loadingPhase
	) {
		auto& context = Amethyst::GetContext();
		context.mPackManager->AddResourcePacksToStack(repository, stack);
		_VanillaGameModuleClient_initializeResourceStack(self, experiments, repository, stack, baseGameVer, loadingPhase);
	}
	#pragma endregion
	#pragma region Item
	Amethyst::InlineHook<decltype(&Item::appendFormattedHovertext)> _Item_appendFormattedHovertext;
	void Item_appendFormattedHovertext(const Item* self, const ItemStackBase& stack, Level& level, std::string& hovertext, bool showCategory) {
		_Item_appendFormattedHovertext(self, stack, level, hovertext, showCategory);
		std::string itemNamespace = self->mNamespace;
		std::string modName;
		std::weak_ptr<const Amethyst::Mod> mod;
		if (itemNamespace.empty() || itemNamespace == "minecraft") {
			modName = "Minecraft";
		} else if (!(mod = Amethyst::GetContext().mModLoader->GetModByNamespace(itemNamespace)).expired()) {
			modName = mod.lock()->mInfo->FriendlyName;
		} else {
			modName.reserve(itemNamespace.size());
			bool cap = true;
			for (char c : itemNamespace) {
				if (c == '_') {
					modName.push_back(' ');
					cap = true;
				} else if (cap) {
					modName.push_back(static_cast<char>(std::toupper(static_cast<unsigned char>(c))));
					cap = false;
				} else {
					modName.push_back(c);
				}
			}
		}

		if (ShowAdvancedItemInfo) {
			std::string itemDataLocalized = "text.amethyst.item_data"_i18n;
			std::string blockTagsLocalized = "text.amethyst.block_tags"_i18n;
			std::string itemTagsLocalized = "text.amethyst.item_tags"_i18n;
			std::string nbtCountLocalized = "text.amethyst.nbt_count"_i18n;

			hovertext += std::format("\n§8{}§r", self->mFullName.getString());
			if (stack.mAuxValue != 0 && stack.mAuxValue != 0x7fff)
				hovertext += "\n" + std::vformat(itemDataLocalized, std::make_format_args(stack.mAuxValue));

			auto block = self->getLegacyBlock();
			if (block && !block->mTags.empty()) {
				hovertext += "\n" + blockTagsLocalized;
				for (const auto& tag : block->mTags) {
					hovertext += std::format("\n§8  #{}§r", tag.getString());
				}
			}

			if (!self->mTags.empty()) {
				hovertext += "\n" + itemTagsLocalized;
				for (const auto& tag : self->mTags) {
					hovertext += std::format("\n§8  #{}§r", tag.getString());
				}
			}

			if (stack.mUserData) {
				size_t nbtCount = stack.mUserData->mTags.size();
				hovertext += "\n" + std::vformat(nbtCountLocalized, std::make_format_args(nbtCount));
			}
		} else {
			std::string holdTextLocalized = "action.amethyst.show_advanced_item_info"_i18n;

			auto& options = *Amethyst::GetClientCtx().mOptions;
			auto& mapping = *options.getCurrentKeyboardRemapping();
			auto* keymapping = mapping.getKeymappingByAction("key.amethyst.show_advanced_item_info");
			std::string keyName = keymapping ? mapping.getMappedKeyName(*keymapping) : "Unknown";

			if (keymapping && keymapping->isAssigned())
				hovertext += "\n" + std::vformat(holdTextLocalized, std::make_format_args(keyName));
		}

		hovertext += std::format("\n§o§9{}§r", modName);
	}
	#pragma endregion

	void Initialize() {
		auto& hooks = Amethyst::GetHookManager();
		HOOK(ScreenView, setupAndRender);
		HOOK(ClientInstance, $constructor);
		HOOK(ClientInstance, onStartJoinGame);
		HOOK(ClientInstance, requestLeaveGame);
		HOOK(BlockGraphics, initBlocks);
		HOOK(BlockActorRenderDispatcher, initializeBlockEntityRenderers);
		HOOK(VanillaClientInputMappingFactory, _addFullKeyboardGamePlayControls);
		HOOK(VanillaClientInputMappingFactory, _createScreenKeyboardAndMouseMapping);
		VHOOK(VanillaClientInputMappingFactory, createInputMappingTemplates, this);
		HOOK(MouseDevice, feed);
		HOOK(InputHandler, handleButtonEvent);
		HOOK(LevelRenderer, renderLevel);
		HOOK(ScreenController, _handleButtonEvent);
		HOOK(StartMenuScreenController, _registerBindings);
		VHOOK(VanillaGameModuleClient, initializeResourceStack, this);
		VHOOK(Item, appendFormattedHovertext, this);
	}
}
#endif