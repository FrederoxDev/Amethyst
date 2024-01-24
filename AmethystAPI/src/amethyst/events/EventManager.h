#pragma once
#include "amethyst/events/Event.h"
#include "minecraft/src-client/common/client/game/ClientInstance.h"
#include "minecraft/src-client/common/client/gui/ScreenView.h"

namespace Amethyst {
class EventManager {
public:
    Event<ClientInstance*> onStartJoinGame;
    Event<ScreenView*, UIRenderContext*> onRenderUI;
    Event<> beforeTick;
    Event<> afterTick;

    /*
    Clear any events that have been registered
    */
    void Shutdown()
    {
        onStartJoinGame.Shutdown();
        onRenderUI.Shutdown();
        beforeTick.Shutdown();
        afterTick.Shutdown();
    }
};
} // namespace Amethyst