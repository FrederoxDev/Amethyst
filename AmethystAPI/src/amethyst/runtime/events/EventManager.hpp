#pragma once
#include "Event.hpp"
#include "minecraft/src-client/common/client/game/ClientInstance.hpp"
#include "minecraft/src-client/common/client/gui/ScreenView.hpp"
#include "minecraft/src/common/world/item/registry/ItemRegistry.hpp"
#include "minecraft/src/common/world/level/block/definition/BlockDefinitionGroup.hpp"
#include "minecraft/src-client/common/client/renderer/game/LevelRenderer.hpp"
#include "amethyst/runtime/input/InputManager.hpp"

class FrameRenderObject;
class ResourcePackManager;

namespace Amethyst {
    class EventManager {
    public:
        Event<ClientInstance*> onStartJoinGame;
        Event<> onRequestLeaveGame;

        Event<LevelRenderer*, ScreenContext*, FrameRenderObject*> onRenderLevel;
        Event<ScreenView*, UIRenderContext*> beforeRenderUI;
        Event<ScreenView*, UIRenderContext*> afterRenderUI;
        Event<> update;

        Event<InputManager*> registerInputs;
        Event<ItemRegistry*> registerItems;
        Event<BlockDefinitionGroup*> registerBlocks;
        Event<ResourcePackManager&, const Experiments&> initBlockGraphics;

        Event<> beforeModShutdown;
    };
} // namespace Amethyst