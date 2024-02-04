#pragma once
#include "amethyst/events/Event.h"
#include "minecraft/src-client/common/client/game/ClientInstance.h"
#include "minecraft/src-client/common/client/gui/ScreenView.h"
#include "minecraft/src/common/world/item/registry/ItemRegistry.h"

namespace Amethyst {
class EventManager {
public:
    Event<ClientInstance*> onStartJoinGame;
    Event<ScreenView*, UIRenderContext*> onRenderUI;
    Event<> beforeTick;
    Event<> afterTick;
    Event<ItemRegistry*> registerItems;

    /*
    Clear any events that have been registered
    */
    void Shutdown()
    {
        onStartJoinGame.Shutdown();
        onRenderUI.Shutdown();
        beforeTick.Shutdown();
        afterTick.Shutdown();
        registerItems.Shutdown();
    }
};
} // namespace Amethyst