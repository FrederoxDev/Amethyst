#pragma once
#include <vector>
#include "Mod.h"
#include "client/common/client/game/ClientInstance.h"
#include "MinHook.h"
#include "amethyst/HookManager.h"

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
};