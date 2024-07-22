#pragma once
#include <vector>
#include "minecraft/src-client/common/client/options/Options.hpp"
#include <minecraft/src-client/common/client/input/ClientInputHandler.hpp>

class AmethystContext;

namespace Amethyst {
    class InputManager {
    public:
        InputManager(AmethystContext& ctx);
        ~InputManager();

        void _copyVanillaInputs();

    private:
        AmethystContext& mAmethyst;
        bool mHasCopiedVanillaInputs;
        std::multimap<unsigned int, std::pair<bool, std::function<void(enum FocusImpact, IClientInstance&)>>> mVanillaButtonDownHandlerMap;
        std::multimap<unsigned int, std::pair<bool, std::function<void(enum FocusImpact, IClientInstance&)>>> mVanillaButtonUpHandlerMap;
    };
}