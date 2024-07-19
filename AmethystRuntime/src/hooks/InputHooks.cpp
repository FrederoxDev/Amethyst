#include "hooks/InputHooks.hpp"
#include <amethyst/runtime/events/InputEvents.hpp>

SafetyHookInline _addFullKeyboardGamePlayControls;
SafetyHookInline _createInputMappingTemplates;

void addFullKeyboardGamePlayControls(VanillaClientInputMappingFactory* self, KeyboardInputMapping* keyboard, MouseInputMapping* mouse)
{
    Amethyst::InputManager* inputManager = AmethystRuntime::getInputManager();
   _addFullKeyboardGamePlayControls.call(self, keyboard, mouse);

   for (auto& actionName : inputManager->mRegisteredInputs) {
       std::string keyName = "key." + actionName;
       std::string buttonName = "button." + actionName;
       self->createKeyboardAndMouseBinding(keyboard, mouse, &buttonName, &keyName);
   }
}

void createInputMappingTemplates(VanillaClientInputMappingFactory* self, Options* opt) {
    _createInputMappingTemplates.call(self, opt);

    // This function is called once at the very start of the game
    // Later, the registerInputs event is called AmethystRuntime::RunMods() for hot reloading.
    AmethystRuntime::getContext()->mOptions = opt;
    RegisterInputsEvent event(*AmethystRuntime::getInputManager());

    AmethystRuntime::getEventBus()->Invoke(event);
}

void CreateInputHooks()
{
    HookManager* hookManager = AmethystRuntime::getHookManager();

    hookManager->RegisterFunction<&VanillaClientInputMappingFactory::createInputMappingTemplates>("48 89 5C 24 ? 48 89 74 24 ? 55 57 41 56 48 8D AC 24 ? ? ? ? B8 ? ? ? ? E8 ? ? ? ? 48 2B E0 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 48 8B FA");
    hookManager->CreateHook<&VanillaClientInputMappingFactory::createInputMappingTemplates>(_createInputMappingTemplates, &createInputMappingTemplates);

    hookManager->RegisterFunction<&VanillaClientInputMappingFactory::_addFullKeyboardGamePlayControls>("40 55 53 56 57 41 56 48 8B EC 48 83 EC ? 45 0F B6 F1");
    hookManager->CreateHook<&VanillaClientInputMappingFactory::_addFullKeyboardGamePlayControls>(_addFullKeyboardGamePlayControls, &addFullKeyboardGamePlayControls);
}