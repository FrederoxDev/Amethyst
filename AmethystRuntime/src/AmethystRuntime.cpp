#include "AmethystRuntime.h"

std::vector<ModInitializeHooks> g_mod_initialize;
std::vector<ModTick> g_mod_tick;
std::vector<ModStartJoinGame> g_mod_start_join;

void AmethystRuntime::LoadMods() {
    Mod minimap("Minimap");
    m_mods.push_back(minimap);

    for each (auto mod in m_mods)
    {
        FARPROC addr;

        addr = mod.GetFunction("Initialize");
        if (addr != NULL) {
            g_mod_initialize.push_back(reinterpret_cast<ModInitializeHooks>(addr));
        }

        addr = mod.GetFunction("OnTick");
        if (addr != NULL) {
            g_mod_tick.push_back(reinterpret_cast<ModTick>(addr));
        }

        addr = mod.GetFunction("OnStartJoin");
        if (addr != NULL) {
            g_mod_start_join.push_back(reinterpret_cast<ModStartJoinGame>(addr));
        }

        Log::Info("[AmethystRuntime] Loaded '{}'\n", mod.mod_name);
    }
}

void AmethystRuntime::RunMods() {
    try {
        for each (auto init_func in g_mod_initialize) init_func();
    }
    catch (std::exception e) {
        Log::Error("[AmethystRuntime] Exception: {}\n", e.what());
        return;
    }

    while (true) {
        try {
            for each (auto tick_func in g_mod_tick) tick_func();
        }
        catch (std::exception e) {
            Log::Error("[AmethystRuntime] Exception: {}\n", e.what());
            return;
        }

        Sleep(1000 / 20);
        if (GetAsyncKeyState(VK_NUMPAD0)) break;

        if (GetAsyncKeyState('R') & 0x8000) {
            Log::Info("\n[AmethystRuntime] Beginning hot-reload!\n");
            this->Shutdown();
            this->LoadMods();

            Sleep(100);
            return this->RunMods();
        }
    }
}

void AmethystRuntime::Shutdown() {
    for each (auto mod in m_mods) {
        mod.Shutdown();
    }

    m_mods.clear();
    g_mod_initialize.clear();
    g_mod_tick.clear();
    g_mod_start_join.clear();
}