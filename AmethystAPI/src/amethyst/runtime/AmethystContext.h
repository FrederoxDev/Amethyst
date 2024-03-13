#pragma once
#include "minecraft/src-client/common/client/game/ClientInstance.h"
#include "minecraft/src-client/common/client/input/MinecraftInputHandler.h"
#include "amethyst/runtime/HookManager.h"
#include "amethyst/runtime/events/EventManager.h"
#include "amethyst/runtime/input/InputManager.h"

class AmethystContext {
public:
    /**
     * Amethyst Specific stuff
     */
    HookManager mHookManager;
    Amethyst::EventManager mEventManager;
    Amethyst::InputManager mInputManager;

    /**
     * Minecraft Specific stuff
     */
    ClientInstance* mClientInstance = nullptr;
    MinecraftInputHandler* mMcInputHandler = nullptr;
};
