#include "hooks/InputHooks.hpp"
#include <amethyst/runtime/events/InputEvents.hpp>

SafetyHookInline _addFullKeyboardGamePlayControls;
SafetyHookInline _createInputMappingTemplates;

void addFullKeyboardGamePlayControls(VanillaClientInputMappingFactory* self, KeyboardInputMapping* keyboard, MouseInputMapping* mouse)
{   

    for (auto& remapping : AmethystRuntime::getContext()->mOptions->mKeyboardRemappings) {
        //Log::Info("{}", remapping->)
    }


    _addFullKeyboardGamePlayControls.call(self, keyboard, mouse);

    Log::Info("0x{:x} 0x{:x} 0x{:x}", (uintptr_t)self, (uintptr_t)keyboard, (uintptr_t)mouse);

    self->mLayout->mKeymappings.emplace_back(Keymapping ("key.test", {'F'}, true));

    self->createKeyboardAndMouseBinding(*keyboard, *mouse, "test", FocusImpact::Neutral);

    auto& inputManager = *AmethystRuntime::getInputManager();
    inputManager._copyVanillaInputs();
}

void createInputMappingTemplates(VanillaClientInputMappingFactory* self, Options* opt) {
    _createInputMappingTemplates.call(self, opt);

    //// This function is called once at the very start of the game
    //AmethystRuntime::getContext()->mOptions = opt;


    //uintptr_t offset = FindOffsetOfPointer(AmethystRuntime::getContext()->mClientInstance->minecraftGame, opt, 0x60000);
    //Log::Info("offset: {}", offset);
}

void CreateInputHooks()
{
    Amethyst::HookManager* hookManager = AmethystRuntime::getHookManager();

    hookManager->RegisterFunction<&VanillaClientInputMappingFactory::createInputMappingTemplates>("48 89 5C 24 ? 48 89 74 24 ? 55 57 41 56 48 8D AC 24 ? ? ? ? B8 ? ? ? ? E8 ? ? ? ? 48 2B E0 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 48 8B FA");
    hookManager->CreateHook<&VanillaClientInputMappingFactory::createInputMappingTemplates>(_createInputMappingTemplates, &createInputMappingTemplates);

    hookManager->RegisterFunction<&VanillaClientInputMappingFactory::_addFullKeyboardGamePlayControls>("40 55 53 56 57 41 56 48 8B EC 48 83 EC ? 45 0F B6 F1");
    hookManager->CreateHook<&VanillaClientInputMappingFactory::_addFullKeyboardGamePlayControls>(_addFullKeyboardGamePlayControls, &addFullKeyboardGamePlayControls);
}