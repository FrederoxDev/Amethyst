#pragma once

#include <string>
#include <vector>
#include <functional>

#include "common/client/input/InputHandler.h"

class InputManager {
public:
    /**
     * Creates a new input action and assigns the default key
     * Needs to be called from mod function: RegisterInputs
     * The game has to be reloaded to register a new input action
    */
    virtual void RegisterInput(const std::string& actionName, int defaultButton, bool allowRemapping = true) = 0;

    /**
     * Add a callback to the input action on the first frame that the button is pressed
     * Should be called from mod function Initialize for hot-reloading button functionality
    */
    virtual void AddButtonDownHandler(const std::string& actionName, std::function<void(FocusImpact, IClientInstance&)> handler) = 0;

    /**
     * Add a callback to the input action on the first frame that the button is released
     * Should be called from mod function Initialize for hot-reloading button functionality
    */
    virtual void AddButtonUpHandler(const std::string& actionName, std::function<void(FocusImpact, IClientInstance&)> handler) = 0;
};