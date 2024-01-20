#include "dllmain.h"

// Define the NtSuspendThread function signature
typedef NTSTATUS(NTAPI* NtSuspendThreadPtr)(HANDLE ThreadHandle, PULONG PreviousSuspendCount);
// Define the NtResumeThread function signature
typedef NTSTATUS(NTAPI* NtResumeThreadPtr)(HANDLE ThreadHandle, PULONG PreviousSuspendCount);

// Define the Amethyst Init function signature
typedef void(__cdecl* AmethystInitPtr)(DWORD dMcThreadID, HANDLE hMcThreadHandle);

// Remove this line if you aren't proxying any functions.
HMODULE hProxied = LoadLibrary(L"C:\\Windows\\System32\\dxgi.dll");
HMODULE hAmethyst = NULL;

HMODULE hClientModule = NULL;
DWORD dMcThreadID = NULL;
HANDLE hMcThreadHandle = NULL;

NtSuspendThreadPtr NtSuspendThread = NULL; // NtSuspendThread function pointer
NtResumeThreadPtr NtResumeThread = NULL; // NtResumeThread function pointer
AmethystInitPtr AmethystInit = NULL; // Amethyst Init function pointer

static Config loadConfig(const std::wstring& path)
{
    // Read the config file and make sure that if exists
    std::ifstream configStream(path);
    if (!configStream.good()) {
        std::wcout << "[AmethystProxy] Failed to open '" << path << "'" << std::endl;
        std::wcout << L"Error" << std::strerror(errno) << std::endl;
        ShutdownWait();
    }

    // Read the configs content and close the config file
    std::string rawConfigJson((std::istreambuf_iterator<char>(configStream)), std::istreambuf_iterator<char>());
    configStream.close();

    try {
        return Config(rawConfigJson);
    }
    catch (...) {
        Log::Error("[AmethystProxy] Failed to parse the config file");
        ShutdownWait();
    }
}

void SuspendMinecraftThread()
{
	NtSuspendThread(hMcThreadHandle, NULL);
}

static std::wstring FindRuntimeDllPath()
{
	wchar_t buffer[MAX_PATH];
    size_t pathLength = GetEnvironmentVariable(L"LOCALAPPDATA", buffer, MAX_PATH);

    std::wstring appdataPath(buffer, pathLength);
    std::wstring configPath = appdataPath + L"\\Amethyst\\launcher_config.json";

    Config config = loadConfig(configPath);
    std::string rawModName = config.injectedMod;
    
    // Split the runtime mod name by the @ character to find the dllName
    size_t at = rawModName.find("@");
    if (at == std::string::npos) {
        Log::Error("[AmethystProxy] Invalid runtime name, no versioning: '{}'", rawModName);
        ShutdownWait();
    }

    // Mod name before the versioning
    std::string modName = rawModName.substr(0, at);
    std::wstring versionlessName(modName.begin(), modName.end());
    std::wstring versionedName(rawModName.begin(), rawModName.end());

    std::wstring dllPath = appdataPath + L"\\Amethyst\\mods\\" + versionedName + L"\\" + versionlessName + L".dll";
    return dllPath;
}

static void InjectIntoMinecraft(std::wstring& path)
{
    LoadLibrary(path.c_str());
}

static void Proxy()
{
    Log::InitializeConsole();
    Log::Info("[AmethystProxy] Using 'AmethystProxy@{}'", PROXY_VERSION);
    Log::Info("[AmethystProxy] McThreadID: {}, McThreadHandle: {}", dMcThreadID, hMcThreadHandle);

    HMODULE ntdllHandle = GetModuleHandle(L"ntdll.dll");
    if (ntdllHandle == 0) {
        Log::Error("[AmethystProxy] Could not get ntdll.dll");
        ShutdownWait();
        return;
    }

    FARPROC _NtSuspendThread = GetProcAddress(ntdllHandle, "NtSuspendThread");
    if (_NtSuspendThread == 0) {
        Log::Error("[AmethystProxy] Could not find ProcAddress of NtSuspendThread in ntdll.dll");
        ShutdownWait();
        return;
    }

    NtSuspendThread = (NtSuspendThreadPtr)_NtSuspendThread;

    SuspendMinecraftThread();
    std::wstring path = FindRuntimeDllPath();
    InjectIntoMinecraft(path);

    HMODULE amethystHandle = GetModuleHandle(L"AmethystRuntime.dll");
    if (amethystHandle == 0) {
        Log::Error("[AmethystProxy] Could not get AmethystRuntime.dll");
        ShutdownWait();
        return;
    }

    FARPROC _AmethystInit = GetProcAddress(amethystHandle, "Init");
    if (_AmethystInit == 0) {
        Log::Error("[AmethystProxy] Could not find ProcAddress of Init in AmethystRuntime.dll");
        ShutdownWait();
        return;
    }

    AmethystInit = (AmethystInitPtr)_AmethystInit;
    AmethystInit(dMcThreadID, hMcThreadHandle);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        hClientModule = GetModuleHandle(NULL);
        // Create a seperate thread to do the proxying after caching the currentThreadID
        dMcThreadID = GetCurrentThreadId();
        hMcThreadHandle = OpenThread(THREAD_ALL_ACCESS, FALSE, dMcThreadID);

        // Create a thread to do the proxying
        CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Proxy, NULL, NULL, NULL);
    }

    return TRUE;
}

DWORD __stdcall EjectThread(LPVOID lpParameter)
{
    ExitProcess(0);
}

void Shutdown()
{
    Log::DestroyConsole();
    CreateThread(0, 0, EjectThread, 0, 0, 0);
}

void ShutdownWait()
{
    Log::Info("Press Numpad0 to close...");

    while (1) {
        Sleep(10);
        if (GetAsyncKeyState(VK_NUMPAD0)) break;
    }

    Shutdown();
}