#pragma once
#include <vector>
#include "Mod.h"
#include "client/common/client/game/ClientInstance.h"

typedef void(*ModInitializeHooks)();
typedef void(*ModTick)();
typedef void(*ModStartJoinGame)(ClientInstance*);

class AmethystRuntime {
private:
	std::vector<Mod> m_mods;

public:
	void LoadMods();
	void RunMods();
	void Shutdown();
};