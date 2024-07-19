#pragma once
#include "amethyst/runtime/HookManager.hpp"
#include "amethyst/runtime/events/EventBus.hpp"
#include "amethyst/runtime/input/InputManager.hpp"
#include "amethyst/runtime/minecraft/MinecraftPackageInfo.hpp"
#include "amethyst/runtime/mod/Mod.hpp"
#include "amethyst/runtime/patchManager/PatchManager.hpp"
#include "amethyst/runtime/EnumAllocator.hpp"
#include "amethyst/MinecraftVtables.hpp"
#include "minecraft/src-client/common/client/game/ClientInstance.hpp"
#include "minecraft/src-client/common/client/input/MinecraftInputHandler.hpp"
#include "minecraft/src-client/common/client/options/Options.hpp"
#include "minecraft/src-client/common/client/renderer/screen/MinecraftUIRenderContext.hpp"
#include "amethyst/runtime/RuntimeFeatures.hpp"

class AmethystContext {
public:
    // Volatile between mod loads
    std::unique_ptr<HookManager> mHookManager;
    std::unique_ptr<Amethyst::EventBus> mEventBus;
    std::unique_ptr<Amethyst::InputManager> mInputManager;
    std::unique_ptr<Amethyst::PatchManager> mPatchManager;
    std::unique_ptr<Amethyst::EnumAllocator> mEnumAllocator;
    std::unique_ptr<Amethyst::RuntimeFeatures> mFeatures;
    std::vector<Mod> mMods;

    // Non-volatile
    Amethyst::MinecraftPackageInfo mPackageInfo;
    ClientInstance* mClientInstance = nullptr;
    MinecraftInputHandler* mMcInputHandler = nullptr;
    Options* mOptions = nullptr;

    // prevent copying
    AmethystContext(const AmethystContext&) = delete;
    friend class AmethystRuntime;

protected:
    virtual void Start() = 0;
    virtual void Shutdown() = 0;
    AmethystContext() = default;
};