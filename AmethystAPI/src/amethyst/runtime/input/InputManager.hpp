#pragma once
#include <vector>
#include "minecraft/src-client/common/client/options/Options.hpp"
#include <minecraft/src-client/common/client/input/ClientInputHandler.hpp>

class AmethystContext;

namespace Amethyst {
    class InputManager {
    public:
        InputManager(AmethystContext* amethyst);
        void RegisterNewInput(std::string actionName, std::vector<int> keys, bool allowRemapping = true);
        void AddButtonDownHandler(const std::string& actionName, std::function<void(FocusImpact, IClientInstance&)> handler, bool suspendable);
        void AddButtonUpHandler(const std::string& actionName, std::function<void(FocusImpact, IClientInstance&)> handler, bool suspendable);

    private:
        void Shutdown();
        void RemoveButtonHandlers();

    public:
        std::vector<std::string> mRegisteredInputs;

    private:
        AmethystContext* mAmethyst;

        friend class AmethystRuntime;
    };
}