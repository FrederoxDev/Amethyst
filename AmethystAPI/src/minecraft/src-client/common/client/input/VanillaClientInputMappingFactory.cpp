#include "minecraft/src-client/common/client/input/VanillaClientInputMappingFactory.hpp"
#include <minecraft/src-client/common/client/input/RemappingLayout.hpp>

void VanillaClientInputMappingFactory::createKeyboardAndMouseBinding(KeyboardInputMapping& keyboard, MouseInputMapping& mouse, const std::string& actionName, FocusImpact focusImpact) const
{
    std::string keyName = "key." + actionName;
    std::string buttonName = "button." + actionName;

    Keymapping keymapping = mLayout->getKeymappingByAction(keyName);

    bool isAltKey = keymapping.isAltKey();
    bool isAssigned = keymapping.isAssigned();

    if (isAltKey || !isAssigned) return;

    for (auto& keyCode : keymapping.mKeys) {
        if (isAltKey) {
            mouse.buttonBindings.emplace_back(buttonName, keyCode);
        }
        else {
            keyboard.keyBindings.emplace_back(buttonName, keyCode, focusImpact);
        }
    }
}
