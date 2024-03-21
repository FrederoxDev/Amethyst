#pragma once
#include "hooks/Hooks.h"
#include "hooks/InputHooks.h"
#include "mod/Mod.h"
#include <amethyst/Config.h>
#include <amethyst/Log.h>
#include <amethyst/MinecraftVtables.h>
#include <amethyst/runtime/AmethystContext.h>
#include <amethyst/runtime/events/Event.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <minecraft/src/common/world/item/Item.h>
#include <vector>

namespace fs = std::filesystem;

typedef void (*ModInitialize)(AmethystContext* context);

/*
 Entry:
 - Initialize console

 Hot-reloading:
 - Initialize MinHook
 - Load mod Dlls and find any mod functions
 - Create hooks that are time dependant
 - If dev mode, prompt a debugger
 - Create regular hooks then call all loaded mods initialize functions
*/
class AmethystRuntime {
private:
    // AmethystRuntime is a Singleton so don't allow creating from outside
    AmethystRuntime() {}
    AmethystRuntime(const AmethystRuntime&);
    AmethystRuntime& operator=(const AmethystRuntime&) = delete;
    static AmethystRuntime* instance;

public:
    static AmethystRuntime* getInstance()
    {
        if (instance == nullptr) instance = new AmethystRuntime();
        return instance;
    }

    static AmethystContext* getContext() 
    {
        return &AmethystRuntime::getInstance()->mAmethystContext;
    }

    static HookManager* getHookManager()
    {
        return &AmethystRuntime::getInstance()->mAmethystContext.mHookManager;
    }

    static Amethyst::EventManager* getEventManager() 
    {
        return &AmethystRuntime::getInstance()->mAmethystContext.mEventManager;
    }

    static Amethyst::InputManager* getInputManager() 
    {
        return &AmethystRuntime::getInstance()->mAmethystContext.mInputManager;
    }

    static Amethyst::PatchManager* getPatchManager() 
    {
        return &AmethystRuntime::getInstance()->mAmethystContext.mPatchManager;
    }

    static std::vector<Amethyst::ModInfo>* getModInfo()
    {
        return &AmethystRuntime::getInstance()->mAmethystContext.mModInfo;
    }


    void Start();
    void Shutdown();

private:
    void ReadLauncherConfig();
    void LoadModDlls();
    void PromptDebugger();
    void CreateOwnHooks();
    void RunMods();
    void ResumeGameThread();
    void PauseGameThread();

    template <typename T>
    void _LoadModFunc(std::vector<T>* vector, Mod& mod, const char* functionName);

private:
    Config mLauncherConfig;
    std::vector<Mod> mLoadedMods;
    AmethystContext mAmethystContext;

public:
    // Mod Functions
    std::vector<ModInitialize> mModInitialize;
};