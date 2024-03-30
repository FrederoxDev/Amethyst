#pragma once
#include <vector>
#include "minecraft/src-client/common/client/options/Options.h"
#include "amethyst/Log.h"

class AmethystContext;

namespace Amethyst {
    class InputManager {
    public:
        InputManager(AmethystContext* amethyst);
        void RegisterNewInput(std::string actionName, std::vector<int> keys, bool allowRemapping = true);
        void Shutdown();

    private:
        AmethystContext* mAmethyst;
        std::vector<std::string> mRegisteredInputs;
    };
}