#pragma once
#include "amethyst/runtime/HookManager.h"
#include "amethyst/runtime/events/EventManager.h"
#include "amethyst/runtime/input/InputManager.h"
#include "amethyst/runtime/mod_info/ModInfo.h"
#include "amethyst/runtime/patchManager/PatchManager.h"
#include "minecraft/src-client/common/client/game/ClientInstance.h"
#include "minecraft/src-client/common/client/input/MinecraftInputHandler.h"

class AmethystContext {
public:
    /**
     * Amethyst Specific stuff
     */
    HookManager mHookManager;
    Amethyst::EventManager mEventManager;
    Amethyst::InputManager mInputManager;
    Amethyst::PatchManager mPatchManager;
    std::vector<Amethyst::ModInfo> mModInfo;

    /**
     * Minecraft Specific stuff
     */
    ClientInstance* mClientInstance = nullptr;
    MinecraftInputHandler* mMcInputHandler = nullptr;
};
