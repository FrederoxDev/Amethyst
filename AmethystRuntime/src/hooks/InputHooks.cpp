#include "hooks/InputHooks.h"

SafetyHookInline _assignDefaultMapping;
SafetyHookInline _addFullKeyboardGamePlayControls;
SafetyHookInline __registerInputHandlers;

static void assignDefaultMapping(RemappingLayout* self, std::vector<Keymapping>** mapping)
{
    RuntimeInputManager* inputManager = AmethystRuntime::getInputManager();

    for (auto& input : inputManager->mInputActions) {
        std::string keyName = "key." + input.mActionName;
        Keymapping keymapping(keyName, {input.mDefaultKey}, input.mAllowRemapping);
        (*mapping)->emplace_back(keymapping);
    }

    _assignDefaultMapping.call<void, RemappingLayout*, std::vector<Keymapping>**>(self, mapping);
}

static void addFullKeyboardGamePlayControls(VanillaClientInputMappingFactory* self, KeyboardInputMapping* keyboard, MouseInputMapping* mouse)
{
    _addFullKeyboardGamePlayControls
        .call<void, VanillaClientInputMappingFactory*, KeyboardInputMapping*, MouseInputMapping*>(self, keyboard, mouse);

    RuntimeInputManager* inputManager = AmethystRuntime::getInputManager();

    for (auto& input : inputManager->mInputActions) {
        std::string keyName = "key." + input.mActionName;
        std::string buttonName = "button." + input.mActionName;
        self->createKeyboardAndMouseBinding(keyboard, mouse, &buttonName, &keyName);
    }
}

static void _registerInputHandlers(MinecraftInputHandler* self)
{
    __registerInputHandlers.call<void, MinecraftInputHandler*>(self);
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

    hookManager->RegisterFunction(&RemappingLayout::assignDefaultMapping, "48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8B EC 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 4C 8B C2");
    hookManager->CreateHook(&RemappingLayout::assignDefaultMapping, _assignDefaultMapping, &assignDefaultMapping);

    hookManager->RegisterFunction(&VanillaClientInputMappingFactory::_addFullKeyboardGamePlayControls, "40 55 53 56 57 41 56 48 8B EC 48 83 EC ? 45 0F B6 F1");
    hookManager->CreateHook(&VanillaClientInputMappingFactory::_addFullKeyboardGamePlayControls, _addFullKeyboardGamePlayControls, &addFullKeyboardGamePlayControls);

    hookManager->RegisterFunction(&MinecraftInputHandler::_registerInputHandlers, "48 89 5C 24 ? 55 56 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B F1 48 8D 05");
    hookManager->CreateHook(&MinecraftInputHandler::_registerInputHandlers, __registerInputHandlers, &_registerInputHandlers);
}