#pragma once
#include "amethyst/runtime/HookManager.hpp"
#include "amethyst/runtime/events/EventManager.hpp"
#include "amethyst/runtime/input/InputManager.hpp"
#include "amethyst/runtime/minecraft/MinecraftPackageInfo.hpp"
#include "amethyst/runtime/mod/Mod.hpp"
#include "amethyst/runtime/patchManager/PatchManager.hpp"
#include "minecraft/src-client/common/client/game/ClientInstance.hpp"
#include "minecraft/src-client/common/client/input/MinecraftInputHandler.hpp"
#include "minecraft/src-client/common/client/options/Options.hpp"

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
    Amethyst::MinecraftPackageInfo mMinecraftPackageInfo;

    /**
     * Minecraft Specific stuff
     */
    ClientInstance* mClientInstance = nullptr;
    MinecraftInputHandler* mMcInputHandler = nullptr;
    Options* mOptions = nullptr;

    AmethystContext()
        : mInputManager(this)
    {}
};
