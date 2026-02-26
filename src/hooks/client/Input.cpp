#ifdef CLIENT
#include "hooks/client/Input.hpp"

#include <amethyst/runtime/events/InputEvents.hpp>
#include <amethyst/runtime/ModContext.hpp>
#include <amethyst/runtime/utility/InlineHook.hpp>

#include <mc/src-deps/input/MouseDevice.hpp>
#include <mc/src-deps/input/InputHandler.hpp>
#include <mc/src-client/common/client/input/VanillaClientInputMappingFactory.hpp>

namespace Amethyst::ClientHooks::InputHooks {
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

	void Initialize() {
		auto& hooks = Amethyst::GetHookManager();
		// VHOOK(VanillaClientInputMappingFactory, createInputMappingTemplates, this);
		// HOOK(VanillaClientInputMappingFactory, _addFullKeyboardGamePlayControls);
		// HOOK(VanillaClientInputMappingFactory, _createScreenKeyboardAndMouseMapping);
		// HOOK(InputHandler, handleButtonEvent);
		// HOOK(MouseDevice, feed);
	}
}
#endif