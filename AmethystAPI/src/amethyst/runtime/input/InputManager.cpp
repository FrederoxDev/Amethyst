#include "amethyst/runtime/input/InputManager.h"
#include "amethyst/runtime/AmethystContext.h"

Amethyst::InputManager::InputManager(AmethystContext *amethyst) {
    mAmethyst = amethyst;
}

void Amethyst::InputManager::RegisterNewInput(
        std::string actionName,
        std::vector<int> keys,
        bool allowRemapping
){
    Options* opt = mAmethyst->mOptions;
    if (!opt) {
        Assert("AmethystContext->mOptions was null, ensure that RegisterNewInput is being called in the RegisterInputs event.");
    }

    for (auto& layout : opt->mKeyboardRemappings)
    {
        Keymapping keymapping("key." + actionName, keys, allowRemapping);
        layout->mKeymappings.emplace_back(keymapping);
        layout->mDefaultMappings.emplace_back(keymapping);
    }

    mRegisteredInputs.emplace_back(actionName);
}

void Amethyst::InputManager::Shutdown() {
    for (auto& actionName : mRegisteredInputs) {
        Log::Info("Removing {}", actionName);
    }

    mRegisteredInputs.clear();
}
