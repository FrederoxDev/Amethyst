#include "amethyst/runtime/input/InputManager.h"

void Amethyst::InputManager::RegisterNewInput(const std::string& inputName, int defaultButton, bool allowRemapping) {
    const InputAction inputAction(inputName, defaultButton, allowRemapping);
    mInputActions.push_back(inputAction);
    Log::Info("made a new input action {} :)", inputName);
}

void Amethyst::InputManager::Shutdown() 
{
    // Remove any input listeners
    // Remove bindings in VanillaClientInputMappingFactory
    // Remove any things in the RemappingLayout
}