#pragma once
#include "MinHook.h"
#include "Mod.h"
#include "Utils.h"
#include "amethyst/Config.h"
#include "amethyst/HookManager.h"
#include "minecraft/src-client/common/client/game/ClientInstance.h"
#include "minecraft/src-client/common/client/gui/ScreenView.h"
#include <fstream>
#include <sstream>
#include <vector>

typedef void (*ModInitializeHooks)();
typedef char*(*ModGetVersion)();
typedef void (*ModTick)();
typedef void (*ModStartJoinGame)(ClientInstance* clientInstance);
typedef void (*ModShutdown)();
typedef void (*ModRender)(ScreenView* screenView, UIRenderContext* ctx);

class AmethystRuntime {
private:
    std::vector<Mod> m_mods;

public:
    void InitializeHooks();
    void LoadMods();
    void RunMods();
    void Shutdown();

private:
    Config ReadConfig();
    void AttachDebugger();
};

extern AmethystRuntime g_runtime;
extern HookManager g_hookManager;