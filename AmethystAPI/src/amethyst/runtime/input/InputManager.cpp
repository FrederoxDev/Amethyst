#include "amethyst/runtime/input/InputManager.h"

void Amethyst::InputManager::RegisterNewInput(const std::string& inputName, int defaultButton, bool allowRemapping) {
    const InputAction inputAction(inputName, defaultButton, allowRemapping);
    mInputActions.push_back(inputAction);
}
