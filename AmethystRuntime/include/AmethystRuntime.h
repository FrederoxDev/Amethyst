#pragma once
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
#include <amethyst/Log.h>
#include <amethyst/Config.h>
#include <amethyst/HookManager.h>
#include "MinHook.h"
#include "mod/Mod.h"
#include "mod/ModFunctions.h"
#include "hooks/Hooks.h"

namespace fs = std::filesystem;

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
    static AmethystRuntime* getInstance() {
        if (instance == nullptr) instance = new AmethystRuntime();
        return instance;
    }

    void Start();
    void Shutdown();
    HookManager* getHookManager();

private:
    void ReadLauncherConfig();
    void LoadModDlls();
    void CreateEarlyHooks();
    void PromptDebugger();
    void CreateOwnHooks();
    void RunMods();

    template <typename T>
    void _LoadModFunc(std::vector<T>* vector, Mod& mod, const char* functionName);

private:
    Config mLauncherConfig;
    HookManager mHookManager;
    std::vector<Mod> mLoadedMods;
   
public:
    // Mod Functions
    std::vector<ModInitialize> mModInitialize;
    std::vector<ModTick> mModTick;
    std::vector<ModStartJoinGame> mModStartJoinGame;
    std::vector<ModShutdown> mModShutdown;
    std::vector<ModRender> mModRender;
};