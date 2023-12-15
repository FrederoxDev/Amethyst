#pragma once
#include <vector>
#include "Mod.h"
#include "minecraft/src-client/common/client/game/ClientInstance.h"
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

class AmethystRuntime {
private:
	std::vector<Mod> m_mods;

public:
	void LoadMods();
	void RunMods();
	void Shutdown();

private:
	Config ReadConfig();
	void AttachDebugger();
};