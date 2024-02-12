#pragma once
#include "amethyst/events/Event.h"
#include "minecraft/src-client/common/client/game/ClientInstance.h"
#include "minecraft/src-client/common/client/gui/ScreenView.h"
#include "minecraft/src/common/world/item/registry/ItemRegistry.h"
#include "minecraft/src/common/world/level/block/definition/BlockDefinitionGroup.h"

namespace Amethyst {
class EventManager {
public:
    Event<ClientInstance*> onStartJoinGame;
    Event<> onRequestLeaveGame;

    Event<ScreenView*, UIRenderContext*> onRenderUI;
    Event<> update;

    Event<ItemRegistry*> registerItems;
    Event<BlockDefinitionGroup*> registerBlocks;

    /*
    Clear any events that have been registered
    */
    void Shutdown()
    {
        onStartJoinGame.Shutdown();
        onRequestLeaveGame.Shutdown();
        onRenderUI.Shutdown();
        update.Shutdown();
        registerItems.Shutdown();
        registerBlocks.Shutdown();
    }
};
} // namespace Amethyst