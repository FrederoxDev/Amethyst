#include "hooks/InputHooks.h"

SafetyHookInline _assignDefaultMapping;
SafetyHookInline _addFullKeyboardGamePlayControls;
SafetyHookInline __registerInputHandlers;

void assignDefaultMapping(RemappingLayout* self, std::vector<Keymapping>&& mapping)
{
    Amethyst::InputManager* inputManager = AmethystRuntime::getInputManager();
    _assignDefaultMapping.call(self, std::move(mapping));

    for (auto& input : inputManager->mInputActions)
    {
        std::string keyName = "key." + input.mInputName;
        Keymapping keymapping(keyName, {input.mDefaultButton}, input.mAllowRemapping);
        mapping.emplace_back(keymapping);
    }

    Log::Info("assignDefaultMapping");
}

void addFullKeyboardGamePlayControls(VanillaClientInputMappingFactory* self, KeyboardInputMapping* keyboard, MouseInputMapping* mouse)
{
    Amethyst::InputManager* inputManager = AmethystRuntime::getInputManager();
   _addFullKeyboardGamePlayControls.call(self, keyboard, mouse);

   for (auto& input : inputManager->mInputActions) {
       std::string keyName = "key." + input.mInputName;
       std::string buttonName = "button." + input.mInputName;
       self->createKeyboardAndMouseBinding(keyboard, mouse, &buttonName, &keyName);
   }

   Log::Info("addFullKeyboardGamePlayControls");
}

void _registerInputHandlers(MinecraftInputHandler* self)
{
    __registerInputHandlers.call(self);

    //RuntimeInputManager* inputManager = AmethystRuntime::getInputManager();
    //InputHandler* inputHandler = self->mInputHandler.get();

    //for (auto& input : inputManager->mInputActions) {
    //    std::string buttonName = "button." + input.mActionName;

    //    // Register a callback to minecraft which checks if the button has its own callback
    //    // If so call the mods callback else do nothing
    //    auto it = self->mInputHandler->mButtonDownHandlerMap.begin();

    //    self->mInputHandler->registerButtonDownHandler(
    //        buttonName, [&input](FocusImpact focus, IClientInstance client) {
    //            Log::Info("pressed");
    //        }, false);    

    //    self->mInputHandler->registerButtonUpHandler(
    //        buttonName, [&input, inputHandler, buttonName](FocusImpact focus, IClientInstance client) {
    //            Log::Info("released, unregistering");

    //            inputHandler->unregisterHandlersByName(buttonName);

    //            /*if (input.mButtonUpHandler == NULL) return;
    //            input.mButtonUpHandler(focus, client);*/
    //        },
    //        false);
    //}
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