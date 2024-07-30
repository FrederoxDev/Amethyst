#pragma once
#include <amethyst/runtime/events/EventBus.hpp>
#include <amethyst/runtime/input/InputManager.hpp>

class RegisterInputsEvent : public BaseEvent {
public:
    Amethyst::InputManager& inputManager;

    RegisterInputsEvent(Amethyst::InputManager& inputManager)
        : inputManager(inputManager) {}
};

class MouseInputEvent : public CancelableEvent {
public:
    char mActionButtonId;
    char mButtonData;
    short x;
    short y;
    short dx;
    short dy;

    MouseInputEvent(char actionButton, char buttonData, short x, short y, short dx, short dy) 
        : mActionButtonId(actionButton), mButtonData(buttonData), x(x), y(y), dx(dx), dy(dy), CancelableEvent() {}
};