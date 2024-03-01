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
        void AddButtonDownListener(const std::string& inputName, std::function<void(FocusImpact, IClientInstance&)>);

    private:
        std::vector<InputAction> mInputActions;
    };
}