#pragma once
#include "hooks/Hooks.h"
#include "hooks/InputHooks.h"
#include "input/RuntimeInput.h"
#include "mod/Mod.h"
#include "mod/ModFunctions.h"
#include <amethyst/Config.h>
#include <amethyst/HookManager.h>
#include <amethyst/Log.h>
#include <amethyst/events/Event.h>
#include <amethyst/events/EventManager.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
#include <minecraft/src/common/world/item/Item.h>
#include <amethyst/MinecraftVtables.h>

namespace fs = std::filesystem;

typedef void (*ModInitialize)(HookManager* hookManager, Amethyst::EventManager* eventManager);

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

    static HookManager* getHookManager()
    {
        return &AmethystRuntime::getInstance()->mHookManager;
    }

    static Amethyst::EventManager* getEventManager() 
    {
        return &AmethystRuntime::getInstance()->mEventManager;
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
    HookManager mHookManager;
    Amethyst::EventManager mEventManager;
    std::vector<Mod> mLoadedMods;

public:
    // Mod Functions
    std::vector<ModInitialize> mModInitialize;
};