#include "hooks/InputHooks.h"

SafetyHookInline _addFullKeyboardGamePlayControls;
SafetyHookInline __registerInputHandlers;

//void addFullKeyboardGamePlayControls(VanillaClientInputMappingFactory* self, KeyboardInputMapping* keyboard, MouseInputMapping* mouse)
//{
//    Amethyst::InputManager* inputManager = AmethystRuntime::getInputManager();
//   _addFullKeyboardGamePlayControls.call(self, keyboard, mouse);
//
//   for (auto& input : inputManager->mInputActions) {
//       std::string keyName = "key." + input.mInputName;
//       std::string buttonName = "button." + input.mInputName;
//       self->createKeyboardAndMouseBinding(keyboard, mouse, &buttonName, &keyName);
//   }
//}

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

//SafetyHookInline __readKeyboardMapping;
//
//void* _readKeyboardMapping(Options* self, char* a1, char* a2) 
//{
//    Log::Info("readKeyboardMapping");
//    AmethystRuntime::getContext()->mOptions = self;
//    return __readKeyboardMapping.call<void*>(self, a1, a2);
//}

SafetyHookInline _createInputMappingTemplates;

void createInputMappingTemplates(VanillaClientInputMappingFactory* self, Options* opt) {
    _createInputMappingTemplates.call(self, opt);
    
    // This function is called once at the very start of the game
    // Later, the registerInputs event is called AmethystRuntime::RunMods() for hot reloading.
    AmethystRuntime::getContext()->mOptions = opt;
    AmethystRuntime::getEventManager()->registerInputs.Invoke(AmethystRuntime::getInputManager());
}

void CreateInputHooks()
{
    HookManager* hookManager = AmethystRuntime::getHookManager();

    hookManager->RegisterFunction<&VanillaClientInputMappingFactory::createInputMappingTemplates>("48 89 5C 24 ? 48 89 74 24 ? 55 57 41 56 48 8D AC 24 ? ? ? ? B8 ? ? ? ? E8 ? ? ? ? 48 2B E0 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 48 8B FA");
    hookManager->CreateHook<&VanillaClientInputMappingFactory::createInputMappingTemplates>(_createInputMappingTemplates, &createInputMappingTemplates);

    /*hookManager->RegisterFunction(&VanillaClientInputMappingFactory::_addFullKeyboardGamePlayControls, "40 55 53 56 57 41 56 48 8B EC 48 83 EC ? 45 0F B6 F1");
    hookManager->CreateHook(&VanillaClientInputMappingFactory::_addFullKeyboardGamePlayControls, _addFullKeyboardGamePlayControls, &addFullKeyboardGamePlayControls);*/

    // 48 89 5C 24 ? 55 56 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B F1 48 8D 05
    /*hookManager->RegisterFunction(&MinecraftInputHandler::_registerInputHandlers, "48 89 5C 24 ? 55 56 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B F1 48 8D 05");
    hookManager->CreateHook(&MinecraftInputHandler::_registerInputHandlers, __registerInputHandlers, &_registerInputHandlers);*/
}