#include "common/client/input/VanillaClientInputMappingFactory.h"

//void VanillaClientInputMappingFactory::_bindActionToKeyboardAndMouseInput(KeyboardInputMapping* keyboardMap, MouseInputMapping* mouseMap, std::string* buttonID, Remapping::ActionEnum action, FocusImpact focusImpact)
//{
//    using function = void(__thiscall*)(VanillaClientInputMappingFactory*, KeyboardInputMapping*, MouseInputMapping*, std::string*, Remapping::ActionEnum, FocusImpact);
//    static auto func = reinterpret_cast<function>(SigScan("40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 49 8B D9 4D 8B F8 4C 8B F2"));
//    return func(this, keyboardMap, mouseMap, buttonID, action, focusImpact);
//}

void VanillaClientInputMappingFactory::createKeyboardAndMouseBinding(KeyboardInputMapping* keyboard, MouseInputMapping* mouse, const std::string* buttonName, const std::string* keyName, FocusImpact impact) {
    Keymapping mapping = mLayout->getKeymappingByAction(keyName);

	for(int key : mapping.mKeys) {
		//key = mLayout->getAdjustedKey(key);
		if (!mapping.isAssigned()) continue;

        if (mapping.isAltKey()) {
            mouse->buttonBindings.emplace_back(buttonName, key);
		}
        else {
            keyboard->keyBindings.emplace_back(buttonName, key, impact);
        }
	}
}