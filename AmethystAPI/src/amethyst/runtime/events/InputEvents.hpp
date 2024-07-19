#pragma once
#include <amethyst/runtime/events/EventBus.hpp>
#include <amethyst/runtime/input/InputManager.hpp>

class RegisterInputsEvent : public BaseEvent {
public:
    Amethyst::InputManager& inputManager;

    RegisterInputsEvent(Amethyst::InputManager& inputManager)
        : inputManager(inputManager) {}
};