#include "dllmain.h"
#include "Log.h"
#include "Hook.h"
#include <vector>
#include <cstdlib>

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Main, NULL, 0, NULL);
    }

    return TRUE;
}

typedef void(*ModInitializeHooks)();
typedef void(*ModTick)();

std::vector<HMODULE> g_hmodules;
std::vector<ModInitializeHooks> g_initialize_hook;
std::vector<ModTick> g_mod_tick;

int LoadMod(const char* mod_name) {
    const char* amethyst_folder = std::getenv("appdata");
    std::string dll_path = std::string(amethyst_folder) + "/Amethyst/mods/" + mod_name + "/" + mod_name + ".dll";

    HMODULE hModDll = LoadLibrary(dll_path.c_str());

    if (hModDll == NULL) {
        DWORD error = GetLastError();

        if (error == 0x5) {
            Log::Error("{}.dll does not have the correct permissions\n", mod_name);
        }
        else {
            Log::Error("Failed to load {}.dll: error code: 0x{:x}", mod_name, error);
        }

        ShutdownWait();
        return 1;
    }

    g_hmodules.push_back(hModDll);

    FARPROC init_addr = GetProcAddress(hModDll, "ModInitializeHooks");
    if (init_addr != NULL) {
        g_initialize_hook.push_back(reinterpret_cast<ModInitializeHooks>(init_addr));
    }
    else {
        DWORD error = GetLastError();
        Log::Info("[{}] ModInitializeHooks was not found! 0x{:x}\n", mod_name, error);
    }

    FARPROC tick_addr = GetProcAddress(hModDll, "ModTick");
    if (tick_addr != NULL) {
        g_mod_tick.push_back(reinterpret_cast<ModTick>(tick_addr));
    }
    else {
        DWORD error = GetLastError();
        Log::Info("[{}] ModTick was not found!0x{:x}\n", mod_name, error);
    }

    return 0;
}

DWORD WINAPI Main() {
    Log::InitializeConsole();
    Log::Info("Minecraft Base Address: 0x{:x}\n", GetMinecraftBaseAddress());
    Log::Info("Minecraft Size: 0x{:x}\n", GetMinecraftSize());

    MH_STATUS status = MH_Initialize();
    if (status != MH_OK) {
        Log::Error("MH_Initialize failed! Reason: {}\n", MH_StatusToString(status));
        ShutdownWait();
        return 1;
    }

    LoadMod("Minimap");

    try {
        for each (auto init in g_initialize_hook)
        {
            init();
        }
    }
    catch (std::exception const&) {
        ShutdownWait();
        return 1;
    }

    while (true) {
        Sleep(50); // Todo: Hook into a minecraft tick function or something

        try {
            for each (auto tick in g_mod_tick)
            {
                tick();
            }
        }
        catch (std::exception const&) {
            ShutdownWait();
            return 1;
        }

        if (GetAsyncKeyState(VK_NUMPAD0)) break;
    }

    Shutdown();
    return 0;
}

DWORD __stdcall EjectThread(LPVOID lpParameter) {
    ExitProcess(0);
}

void Shutdown() {
    Log::DestroyConsole();
    MH_Uninitialize();

    for each (auto hModDll in g_hmodules)
    {
        FreeLibrary(hModDll);
    }

    CreateThread(0, 0, EjectThread, 0, 0, 0);
}

void ShutdownWait() {
    Log::Info("Press Numpad0 to close...\n");

    while (1) {
        Sleep(10);
        if (GetAsyncKeyState(VK_NUMPAD0)) break;
    }

    Shutdown();
}