#include "AmethystRuntime.h"

AmethystRuntime* AmethystRuntime::instance = nullptr;
extern HANDLE gMcThreadHandle;
extern DWORD gMcThreadId;

void AmethystRuntime::Start()
{
    Log::Info("[AmethystRuntime] Using 'AmethystRuntime@{}'", MOD_VERSION);

    // Prompt a debugger if they are in developer mode
    if (mLauncherConfig.promptDebugger) PromptDebugger();

    // read the config file and load in any mods
    ReadLauncherConfig();
    LoadModDlls();

    // Create our hooks then run the mods
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

void AmethystRuntime::PromptDebugger()
{
    Log::Info("[AmethystRuntime] Minecraft's Base: 0x{:x}", GetMinecraftBaseAddress());
    std::string command = fmt::format("vsjitdebugger -p {:d}", GetCurrentProcessId());
    system(command.c_str());
}

void AmethystRuntime::CreateOwnHooks()
{
    static bool hasRegisteredInputsBefore = false;

    if (!hasRegisteredInputsBefore) {
        for (auto& registerInputFunc : mModRegisterInputs) {
            registerInputFunc(getInputManager());
        }

        hasRegisteredInputsBefore = true;
    }

    CreateInputHooks();
    CreateModFunctionHooks();
}

void AmethystRuntime::RunMods()
{
    // Invoke mods to initialize and setup hooks, etc..
    for (auto& modInitialize : mModInitialize)
        modInitialize(getHookManager(), getEventManager(), getInputManager());

    ResumeGameThread();

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
    mEventManager.Shutdown();

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
}

void AmethystRuntime::ResumeGameThread()
{
    typedef NTSTATUS(NTAPI * NtResumeThreadPtr)(HANDLE ThreadHandle, PULONG PreviousSuspendCount);
    static NtResumeThreadPtr NtResumeThread = (NtResumeThreadPtr)GetProcAddress(GetModuleHandle("ntdll.dll"), "NtResumeThread");
    NtResumeThread(gMcThreadHandle, NULL);
}

void AmethystRuntime::PauseGameThread()
{
    typedef NTSTATUS(NTAPI * NtSuspendThreadPtr)(HANDLE ThreadHandle, PULONG PreviousSuspendCount);
    static NtSuspendThreadPtr NtSuspendThread = (NtSuspendThreadPtr)GetProcAddress(GetModuleHandle("ntdll.dll"), "NtSuspendThread");
    NtSuspendThread(gMcThreadHandle, NULL);
}
