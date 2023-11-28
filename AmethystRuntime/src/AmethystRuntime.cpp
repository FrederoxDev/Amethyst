#include "AmethystRuntime.h"

std::vector<ModInitializeHooks> g_mod_initialize;
std::vector<ModTick> g_mod_tick;
std::vector<ModStartJoinGame> g_mod_start_join;
std::vector<ModShutdown> g_mod_shutdown;

void AmethystRuntime::LoadMods() {
    MH_STATUS status = MH_Initialize();
    if (status != MH_OK) {
        Log::Error("MH_Initialize failed! Reason: {}\n", MH_StatusToString(status));
        throw std::exception("MH_Initialize failed!");
    }

    this->AttachDebugger();

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

        addr = mod.GetFunction("Shutdown");
        if (addr != NULL) {
            g_mod_shutdown.push_back(reinterpret_cast<ModShutdown>(addr));
        }
        else {
            Log::Warning("[AmethystRuntime] '{}' does not have 'void Shutdown()'. A mod should remove all hooks here for hot-reloading to work.\n", mod.mod_name);
        }

        Log::Info("[AmethystRuntime] Loaded '{}'\n", mod.mod_name);
    }
}

void AmethystRuntime::RunMods() {
    for each (auto init_func in g_mod_initialize) init_func();

    while (true) {
        for each (auto tick_func in g_mod_tick) tick_func();

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
    // Allow each mod to have its shutdown logic
    for each (auto shutdown_func in g_mod_shutdown) shutdown_func();

    // Unload each mod dll from game memory
    for each (auto mod in m_mods) {
        mod.Free();
    }

    // Remove any existing function addresses to mod funcs
    m_mods.clear();
    g_mod_initialize.clear();
    g_mod_tick.clear();
    g_mod_start_join.clear();
    g_mod_shutdown.clear();

    // Disable MH and remove any created hooks
    MH_Uninitialize();
}

void AmethystRuntime::AttachDebugger() {
    char buffer[100];
    sprintf(buffer, "vsjitdebugger -p %d", GetCurrentProcessId());
    std::string cmd(buffer);

    system(cmd.c_str());
}