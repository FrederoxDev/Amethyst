#pragma once
#include "amethyst/events/Event.h"
#include "minecraft/src-client/common/client/game/ClientInstance.h"
#include "minecraft/src-client/common/client/gui/ScreenView.h"

namespace Amethyst {
/*
Manages all of the created events
TODO: Make the events not all be hardcoded?
*/
class EventManager {
public:
    Event<ClientInstance*> onStartJoinGame;
    Event<ScreenView*, UIRenderContext*> onRenderUI;
    Event<> beforeTick;
    Event<> afterTick;

    /*
    Clear any events that have been registered
    */
    void Shutdown() {
        onStartJoinGame.Shutdown();
        onRenderUI.Shutdown();
        beforeTick.Shutdown();
        afterTick.Shutdown();
    }

    /*
    To Do: Rename this
    */
    template <typename Func>
    void RegisterFunction(Func function) {
        Log::Info("{}", typeid(function).name);
    }
};
} // namespace Amethyst