#pragma once
#include "minecraft/src-client/common/client/game/ClientInstance.h"
#include "amethyst/runtime/HookManager.h"
#include "amethyst/runtime/events/EventManager.h"

class AmethystContext {
public:
    /**
     * Amethyst Specific stuff
     */
    HookManager mHookManager;
    Amethyst::EventManager mEventManager;

    /**
     * Minecraft Specific stuff
     */
    ClientInstance* mClientInstance = nullptr;
};
