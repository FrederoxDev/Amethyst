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
    Options* opt = mAmethyst->mOptions;

    for (auto& actionName : mRegisteredInputs) {
        for (auto& mapping : opt->mKeyboardRemappings) {
            auto newEnd = std::remove_if(
                    mapping->mKeymappings.begin(),
                    mapping->mKeymappings.end(),
                [&actionName](const Keymapping& keymapping)
            {
                  return keymapping.mAction == std::string("key." + actionName);
            });

            // Erase the removed elements from the vector.
            mapping->mKeymappings.erase(newEnd, mapping->mKeymappings.end());
        }
    }

    mRegisteredInputs.clear();
}
