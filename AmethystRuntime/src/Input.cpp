#include "Input.h"

std::string button = "button.test_action";
std::string key = "key.test_action";

RemappingLayout::_assignDefaultMapping _assignDefaultMapping;
VanillaClientInputMappingFactory::__addFullKeyboardGamePlayControls _addFullKeyboardGamePlayControls;
MinecraftInputHandler::__registerInputHandlers _registerInputHandlers;

static void assignDefaultMapping(RemappingLayout* self, std::vector<Keymapping>&& mapping)
{
    Keymapping keymapping(key, {0x52}, true);
    mapping.emplace_back(keymapping);

    _assignDefaultMapping(self, std::move(mapping));
}

static void addFullKeyboardGamePlayControls(VanillaClientInputMappingFactory* self, KeyboardInputMapping* keyboard, MouseInputMapping* mouse)
{
    _addFullKeyboardGamePlayControls(self, keyboard, mouse);
    self->createKeyboardAndMouseBinding(keyboard, mouse, &button, &key);
}

static void registerInputHandlers(MinecraftInputHandler* self)
{
    _registerInputHandlers(self);

    self->mInputHandler->registerButtonDownHandler(
        button, [](FocusImpact focus, IClientInstance& client) {
            Log::Info("{} down", button);
        },
        false);

    self->mInputHandler->registerButtonUpHandler(
        button, [](FocusImpact focus, IClientInstance& client) {
            Log::Info("{} up", button);
        },
        false);
}

void Amethyst::CreateInputHooks(HookManager* hookManager)
{
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