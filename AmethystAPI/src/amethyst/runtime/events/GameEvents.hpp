#pragma once
#include <amethyst/runtime/events/EventBus.hpp>

class ClientInstance;

class OnStartJoinGameEvent : public BaseEvent {
public:
    ClientInstance& client;

    OnStartJoinGameEvent(ClientInstance& client) 
        : client(client) {}
};

class OnRequestLeaveGameEvent : public BaseEvent {
public:
    ClientInstance& client;

    OnRequestLeaveGameEvent(ClientInstance& client)
        : client(client) {}
};

class UpdateEvent : public BaseEvent {
public:
    UpdateEvent() {}
};