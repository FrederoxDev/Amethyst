#pragma once
#include "minecraft/src-deps/input/InputHandler.h"
#include "amethyst/runtime/input/InputAction.h"
#include <vector>

/**
 * Manages creating inputs for an Amethyst Mod
 */
namespace Amethyst {
    class InputManager {
    public:
        void RegisterNewInput(const std::string& inputName, int defaultButton, bool allowRemapping);

    private:
        std::vector<InputAction> mInputActions;
    };
}