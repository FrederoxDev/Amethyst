#pragma once
#include <amethyst/runtime/events/EventBus.hpp>

class ScreenEvent;

class UIButtonHandleEvent : public BaseEvent {
public:
    ScreenEvent& mScreenEvent;

    UIButtonHandleEvent(ScreenEvent& screenEvent) 
        : mScreenEvent(screenEvent) {}
};