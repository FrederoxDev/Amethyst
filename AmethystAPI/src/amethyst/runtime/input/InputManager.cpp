#include <utility>

#include "amethyst/runtime/input/InputManager.hpp"
#include "amethyst/runtime/AmethystContext.hpp"

Amethyst::InputManager::InputManager(AmethystContext *amethyst) {
    mAmethyst = amethyst;

    mAmethyst->mEventManager.onRequestLeaveGame.AddListener([this]() {
        Log::Info("Removing button handlers");
        this->RemoveButtonHandlers();
    });
}

// make this listen to the on start join event, until then cache values.. and make them then
// also listen to the leave event and remove all listeners.

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

    // Remove registered keys.
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

    RemoveButtonHandlers();
    mRegisteredInputs.clear();
}

void Amethyst::InputManager::AddButtonDownHandler(
        const std::string& actionName,
        std::function<void(FocusImpact, IClientInstance &)> handler,
        bool suspendable)
{
    ClientInputHandler* clientInput = mAmethyst->mClientInstance->inputHandler;
    if (clientInput == nullptr) {
        Assert("ButtonHandlers cannot be created in amethyst event RegisterInputs, consider using OnStartJoinGame.");
    }

    InputHandler* inputHandler = clientInput->mInputHandler;
    inputHandler->registerButtonDownHandler("button." + actionName, std::move(handler), suspendable);
}

void Amethyst::InputManager::AddButtonUpHandler(
        const std::string &actionName,
        std::function<void(FocusImpact, IClientInstance &)> handler,
        bool suspendable)
{
    ClientInputHandler* clientInput = mAmethyst->mClientInstance->inputHandler;
    if (clientInput == nullptr) {
        Assert("ButtonHandlers cannot be created in amethyst event RegisterInputs, consider using OnStartJoinGame.");
    }

    InputHandler* inputHandler = clientInput->mInputHandler;
    inputHandler->registerButtonUpHandler("button." + actionName, std::move(handler), suspendable);
}

void Amethyst::InputManager::RemoveButtonHandlers() {
    InputHandler* mcInput = mAmethyst->mClientInstance->inputHandler->mInputHandler;

    // Remove button down listeners
    for (auto& actionName : mRegisteredInputs) {
        uint32_t actionId = StringToNameId("button." + actionName);

        auto it = mcInput->mButtonDownHandlerMap.begin();
        while (it != mcInput->mButtonDownHandlerMap.end()) {
            if (it->first == actionId) {
                it = mcInput->mButtonDownHandlerMap.erase(it);
                continue;
            }
            ++it;
        }

        it = mcInput->mButtonUpHandlerMap.begin();
        while (it != mcInput->mButtonUpHandlerMap.end()) {
            if (it->first == actionId) {
                it = mcInput->mButtonUpHandlerMap.erase(it);
                continue;
            }
            ++it;
        }
    }
}
