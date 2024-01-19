#include "AmethystRuntime.h"

AmethystRuntime* AmethystRuntime::instance = nullptr;

void AmethystRuntime::Start()
{
    Log::Info("[AmethystRuntime] Using 'AmethystRuntime@{}'", MOD_VERSION);
    MH_Initialize();

    // Read launcher_config.json and load mod Dlls
    ReadLauncherConfig();
    LoadModDlls();

    // Create any hooks that are time dependant and need to be done early
    CreateEarlyHooks();

    // Prompt a debugger if they are in developer mode
    if (mLauncherConfig.promptDebugger) PromptDebugger();
    CreateOwnHooks();
    RunMods();
}

void AmethystRuntime::ReadLauncherConfig()
{
    // Ensure it exists
    std::string launcherConfigPath = GetAmethystFolder() + "launcher_config.json";
    if (!fs::exists(launcherConfigPath)) {
        throw std::exception("launcher_config.json could not be found!");
    }

    // Try to read it to a std::string
    std::ifstream configFile(launcherConfigPath);
    if (!configFile.is_open()) {
        throw std::exception("Failed to open launcher_config.json");
    }

    // Read into a std::string
    std::stringstream buffer;
    buffer << configFile.rdbuf();
    configFile.close();
    std::string fileContents = buffer.str();

    mLauncherConfig = Config(fileContents);
}

void AmethystRuntime::LoadModDlls()
{
    // Load all mods from the launcher_config.json
    for (auto& modName : mLauncherConfig.mods) {
        mLoadedMods.emplace_back(modName);
    }

    // Load all mod functions
    for (auto& mod : mLoadedMods) {
        Log::Info("[AmethystRuntime] Loading '{}'", mod.modName);

        _LoadModFunc(&mModRegisterInputs, mod, "RegisterInputs");
        _LoadModFunc(&mModInitialize, mod, "Initialize");
        _LoadModFunc(&mModShutdown, mod, "Shutdown");
    }
}

template <typename T>
void AmethystRuntime::_LoadModFunc(std::vector<T>* vector, Mod& mod, const char* functionName)
{
    FARPROC address = mod.GetFunction(functionName);
    if (address == NULL) return;
    vector->push_back(reinterpret_cast<T>(address));
}

void AmethystRuntime::CreateEarlyHooks()
{
    static bool hasRegisteredBefore = false;

    if (!hasRegisteredBefore) {
        for (auto& registerInputFunc : mModRegisterInputs) {
            registerInputFunc(getInputManager());
        }

        hasRegisteredBefore = true;
    }

    CreateInputHooks();
}

void AmethystRuntime::PromptDebugger()
{
    Log::Info("[AmethystRuntime] Minecraft's Base: 0x{:x}", GetMinecraftBaseAddress());
    std::string command = fmt::format("vsjitdebugger -p {:d}", GetCurrentProcessId());
    system(command.c_str());
}

void AmethystRuntime::CreateOwnHooks()
{
    CreateModFunctionHooks();
}

void AmethystRuntime::RunMods()
{
    // Invoke mods to initialize and setup hooks, etc..
    for (auto& modInitialize : mModInitialize)
        modInitialize(getEventManager(), getInputManager());

    // Listen for hot-reload and keep Amethyst running until the end
    while (true) {
        Sleep(1000 / 20);

        if (GetAsyncKeyState(VK_NUMPAD0)) break;
        if (GetAsyncKeyState('R') & 0x8000) {
            Log::Info("\n========================= Beginning hot-reload! =========================");

            Shutdown();
            return Start();
        }
    }
}

void AmethystRuntime::Shutdown()
{
    // Remove any of the runtime mods hooks
    mHookManager.Shutdown();

    // Unload any input action callbacks from Mod Dlls
    mInputManager.Shutdown();

    // Prompt all mods to shutdown
    for (auto& modShutdown : mModShutdown)
        modShutdown();

    // Unload all mod Dlls
    for (auto& mod : mLoadedMods) {
        mod.Shutdown();
    }

    mLoadedMods.clear();

    // Clear all mod functions
    mModRegisterInputs.clear();
    mModInitialize.clear();
    mModShutdown.clear();

    mEventManager.Shutdown();

    MH_Uninitialize();
}