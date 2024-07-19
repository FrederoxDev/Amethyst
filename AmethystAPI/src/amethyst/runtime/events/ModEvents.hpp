#pragma once
#include <amethyst/runtime/events/EventBus.hpp>

class BeforeModShutdownEvent : public BaseEvent {
public:
    BeforeModShutdownEvent() = default;
};

class AddModEventListenersEvent : public BaseEvent {
public:
    AddModEventListenersEvent() = default;
};