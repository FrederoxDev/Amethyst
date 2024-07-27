#pragma once
#include <amethyst/runtime/events/EventBus.hpp>

class ClientInstance;
class Level;

/*
Called when loading into a world
 - Called on ApplicationView thread
*/
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

class OnLevelConstructed : public BaseEvent {
public:
    Level& mLevel;

    OnLevelConstructed(Level& level) 
        : mLevel(level) {}
};

class OnLevelDestroyed : public BaseEvent {
public:
    OnLevelDestroyed() {};
};