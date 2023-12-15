#pragma once
#include <vector>
#include "Mod.h"
#include "minecraft/src-client/common/client/game/ClientInstance.h"
#include "MinHook.h"
#include "amethyst/HookManager.h"
#include "Utils.h"
#include <fstream>
#include <sstream>
#include "Config.h"
#include "Json.hpp"
using json = nlohmann::json;

typedef void(*ModInitializeHooks)();
typedef void(*ModTick)();
typedef void(*ModStartJoinGame)(ClientInstance* clientInstance);
typedef void(*ModShutdown)();

class AmethystRuntime {
private:
	Config m_config;
	std::vector<Mod> m_mods;

public:
	void LoadMods();
	void RunMods();
	void Shutdown();

private:
	void ReadConfig();
	void AttachDebugger();
};