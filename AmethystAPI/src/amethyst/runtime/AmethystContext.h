#pragma once
#include "amethyst/runtime/HookManager.h"
#include "amethyst/runtime/events/EventManager.h"
#include "amethyst/runtime/input/InputManager.h"
#include "amethyst/runtime/minecraft/MinecraftInfo.h"
#include "amethyst/runtime/mod/Mod.h"
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
    std::vector<Mod> mMods;
    Amethyst::MinecraftInfo mMinecraftInfo;

    /**
     * Minecraft Specific stuff
     */
    ClientInstance* mClientInstance = nullptr;
    MinecraftInputHandler* mMcInputHandler = nullptr;
};
