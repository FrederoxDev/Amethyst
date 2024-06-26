#include "AmethystRuntime.hpp"
#include <AmethystDebugging.hpp>

AmethystRuntime* AmethystRuntime::instance = nullptr;
extern HANDLE gMcThreadHandle;
extern DWORD gMcThreadId;

void AmethystRuntime::Start()
{
    Log::Info("[AmethystRuntime] Using 'AmethystRuntime@{}'", MOD_VERSION);

    SemVersion version = getMinecraftPackageInfo()->mVersion;

    if (version.mMajor != MOD_TARGET_VERSION_MAJOR || version.mMinor != MOD_TARGET_VERSION_MINOR || version.mPatch != MOD_TARGET_VERSION_PATCH) 
    {
        Log::Warning("\nAmethystRuntime@{} has been made for Minecraft version {}.{}.{}, detected version {}.{}.{}\n\t> It should be expected that things may break on this version.\n\t> We will not provide support for unintended versions.\n", 
            MOD_VERSION, 
            MOD_TARGET_VERSION_MAJOR, MOD_TARGET_VERSION_MINOR, MOD_TARGET_VERSION_PATCH,
            version.mMajor, version.mMinor, version.mPatch
        );
    }
    else {
        Log::Info("[AmethystRuntime] Minecraft Version: {}.{}.{}", version.mMajor, version.mMinor, version.mPatch);
    }

    // read the config file and load in any mods
    ReadLauncherConfig();

    // Prompt a debugger if they are in developer mode
    if (mLauncherConfig.promptDebugger) PromptDebugger();

    LoadModDlls(); 

    // Create our hooks then run the mods
    CreateOwnHooks();
    RunMods();
} 

void AmethystRuntime::ReadLauncherConfig()
{
    // Ensure it exists
    fs::path launcherConfigPath = GetAmethystFolder() / "launcher_config.json";

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
        mAmethystContext.mMods.emplace_back(modName);
    }

    // Load all mod functions
    for (auto& mod : mAmethystContext.mMods) {
        Log::Info("[AmethystRuntime] Loading '{}'", mod.modName);
        _LoadModFunc(&mModInitialize, mod, "Initialize");
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
    CreateInputHooks();
    CreateModFunctionHooks();
}

void AmethystRuntime::RunMods()
{
    // Invoke mods to initialize and setup hooks, etc..
    for (auto& modInitialize : mModInitialize)
        modInitialize(&mAmethystContext);

    // If we have hot-reloaded this will be true, so prompt mods to create their inputs.
    if (AmethystRuntime::getContext()->mOptions != nullptr) {
        AmethystRuntime::getEventManager()->registerInputs.Invoke(
            AmethystRuntime::getInputManager()
        );
    }

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
    // Allow mods to do any shutdown logic.
    getEventManager()->beforeModShutdown.Invoke();

    // Unregister any input listeners and remove created input types
    getInputManager()->Shutdown();

    // Destroy all listeners on amethysts event manager.
    getEventManager()->Shutdown();

    // Remove any hooks and clear data for the next load
    getHookManager()->Shutdown();

    // Remove any patches that were applied to the game.
    getPatchManager()->RemoveAllPatches();

    // Reset any allocated enums
    getEnumAllocator()->Shutdown();

    // Unload all mod dll's.
    for (auto& mod : mAmethystContext.mMods) {
        mod.Shutdown();
    }

    // Clear lists of mods & functions.
    mAmethystContext.mMods.clear();
    mModInitialize.clear();
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
