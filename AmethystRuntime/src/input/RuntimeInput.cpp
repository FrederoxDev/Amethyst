#include "input/RuntimeInput.h"

void RuntimeInputManager::RegisterInput(const std::string& actionName, int defaultButton, bool allowRemapping)
{
    InputAction inputAction = {actionName, defaultButton, allowRemapping, NULL, NULL};
    mInputActions.push_back(inputAction);
}

void RuntimeInputManager::AddButtonDownHandler(const std::string& actionName, std::function<void(FocusImpact, IClientInstance&)> handler)
{
    for (auto& input : mInputActions) {
        if (input.mActionName != actionName) continue;
        input.mButtonDownHandler = handler;
        return;
    }

    std::string message = fmt::format("Input Action '{}' has not been registered. Ensure that you have restarted the game after registering a new input action", actionName);
    throw std::exception(message.c_str());
}

void RuntimeInputManager::AddButtonUpHandler(const std::string& actionName, std::function<void(FocusImpact, IClientInstance&)> handler)
{
    for (auto& input : mInputActions) {
        if (input.mActionName != actionName) continue;
        input.mButtonUpHandler = handler;
        return;
    }

    std::string message = fmt::format("Input Action '{}' has not been registered. Ensure that you have restarted the game after registering a new input action", actionName);
    throw std::exception(message.c_str());
}

void RuntimeInputManager::Shutdown()
{
    // Destroy any references to callbacks in an unloaded Dll
    for (auto& input : mInputActions) {
        input.mButtonDownHandler = NULL;
        input.mButtonUpHandler = NULL;
    }
}
