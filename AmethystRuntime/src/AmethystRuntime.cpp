#include "AmethystRuntime.h"

std::vector<ModInitializeHooks> g_mod_initialize;
std::vector<ModTick> g_mod_tick;
std::vector<ModStartJoinGame> g_mod_start_join;
std::vector<ModShutdown> g_mod_shutdown;
std::vector<ModRender> g_mod_render;

Config AmethystRuntime::ReadConfig() {
    // Ensure it exists
    std::string configPath = GetAmethystUWPFolder() + "config.json";
    Log::Info("[AmethystRuntime] Config: {}\n", configPath);

    if (!fs::exists(configPath)) {
        Log::Error("[AmethystRuntime] Could not find config.json\n\tat '{}'\n", configPath);
        throw std::exception();
    }

    std::ifstream configFile(configPath);
    if (!configFile.is_open()) {
        Log::Error("[AmethystRuntime] Failed to open config.json\n\tat '{}'", configPath);
        throw std::exception();
    }
    
    // Read into a std::string
    std::stringstream buffer;
    buffer << configFile.rdbuf();
    configFile.close();
    std::string fileContents = buffer.str();

    return Config(fileContents);
}

void AmethystRuntime::LoadMods() {
    // Initialize MinHook
    MH_STATUS status = MH_Initialize();
    if (status != MH_OK) {
        Log::Error("MH_Initialize failed! Reason: {}\n", MH_StatusToString(status));
        throw std::exception("MH_Initialize failed!");
    }

    // Read config.json file
    Config config = ReadConfig();
    for each (auto& modName in config.mods) {
        this->m_mods.push_back(Mod(modName));
    }

    if (config.promptDebugger) AttachDebugger();

    // Load functions from the mods
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

        addr = mod.GetFunction("OnRenderUI");
        if (addr != NULL) {
            g_mod_render.push_back(reinterpret_cast<ModRender>(addr));
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
    // AmethystRuntime's own Hooks
    InitializeHooks();

    // Allow mods to create hooks
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

ScreenView::_setupAndRender _ScreenView_setupAndRender;

static void* ScreenView_setupAndRender(ScreenView* self, UIRenderContext* ctx) {
    for each (auto render_func in g_mod_render) render_func(self, ctx);

    return _ScreenView_setupAndRender(self, ctx);
}

void AmethystRuntime::InitializeHooks() {
    g_hookManager.CreateHook(
        SigScan("48 8B C4 48 89 58 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 8B FA 48 89 54 24 ? 4C 8B E9 48 89 4C 24"),
        &ScreenView_setupAndRender, reinterpret_cast<void**>(&_ScreenView_setupAndRender)
    );
}

void AmethystRuntime::Shutdown() {
    g_hookManager.Shutdown();

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