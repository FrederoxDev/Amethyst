#pragma once
#include <vector>
#include "Mod.h"
#include "minecraft/src-client/common/client/game/ClientInstance.h"
#include "minecraft/src-client/common/client/gui/ScreenView.h"
#include "MinHook.h"
#include "amethyst/HookManager.h"
#include "Utils.h"
#include <fstream>
#include <sstream>
#include "amethyst/Config.h"

typedef void(*ModInitializeHooks)();
typedef void(*ModTick)();
typedef void(*ModStartJoinGame)(ClientInstance* clientInstance);
typedef void(*ModShutdown)();
typedef void(*ModRender)(ScreenView* screenView, UIRenderContext* ctx);

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