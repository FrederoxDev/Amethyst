#include "hooks/InputHooks.h"

#include "AmethystRuntime.h"

#include <common/client/game/ClientInstance.h>
#include <common/client/input/ClientInputHandler.h>
#include <common/client/input/MinecraftInputHandler.h>
#include <common/client/input/RemappingLayout.h>
#include <common/client/input/VanillaClientInputMappingFactory.h>

RemappingLayout::_assignDefaultMapping _assignDefaultMapping;
VanillaClientInputMappingFactory::__addFullKeyboardGamePlayControls _addFullKeyboardGamePlayControls;
MinecraftInputHandler::__registerInputHandlers _registerInputHandlers;

static void assignDefaultMapping(RemappingLayout* self, std::vector<Keymapping>&& mapping)
{
    RuntimeInputManager* inputManager = AmethystRuntime::getInputManager();

    for (auto& input : inputManager->mInputActions) {
        std::string keyName = "key." + input.mActionName;
        Keymapping keymapping(keyName, {input.mDefaultKey}, input.mAllowRemapping);
        mapping.emplace_back(keymapping);
    }

    _assignDefaultMapping(self, std::move(mapping));
}

static void addFullKeyboardGamePlayControls(VanillaClientInputMappingFactory* self, KeyboardInputMapping* keyboard, MouseInputMapping* mouse)
{
    _addFullKeyboardGamePlayControls(self, keyboard, mouse);
    RuntimeInputManager* inputManager = AmethystRuntime::getInputManager();

    for (auto& input : inputManager->mInputActions) {
        std::string keyName = "key." + input.mActionName;
        std::string buttonName = "button." + input.mActionName;
        self->createKeyboardAndMouseBinding(keyboard, mouse, &buttonName, &keyName);
    }
}

static void registerInputHandlers(MinecraftInputHandler* self)
{
    _registerInputHandlers(self);
    RuntimeInputManager* inputManager = AmethystRuntime::getInputManager();

    for (auto& input : inputManager->mInputActions) {
        std::string buttonName = "button." + input.mActionName;

        // Register a callback to minecraft which checks if the button has its own callback
        // If so call the mods callback else do nothing
        self->mInputHandler->registerButtonDownHandler(
            buttonName, [&input](FocusImpact focus, IClientInstance client) {
                if (input.mButtonDownHandler == NULL) return;
                input.mButtonDownHandler(focus, client);
            },
            false);

        self->mInputHandler->registerButtonUpHandler(
            buttonName, [&input](FocusImpact focus, IClientInstance client) {
                if (input.mButtonUpHandler == NULL) return;
                input.mButtonUpHandler(focus, client);
            },
            false);
    }
}

void CreateInputHooks()
{
    HookManager* hookManager = AmethystRuntime::getHookManager();

    hookManager->CreateHook(
        SigScan("48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8B EC 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 4C 8B C2"),
        &assignDefaultMapping, reinterpret_cast<void**>(&_assignDefaultMapping));

    hookManager->CreateHook(
        SigScan("40 55 53 56 57 41 56 48 8B EC 48 83 EC ? 45 0F B6 F1"),
        &addFullKeyboardGamePlayControls, reinterpret_cast<void**>(&_addFullKeyboardGamePlayControls));

    hookManager->CreateHook(
        SigScan("48 89 5C 24 ? 55 56 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B F1 48 8D 05"),
        &registerInputHandlers, reinterpret_cast<void**>(&_registerInputHandlers));
}