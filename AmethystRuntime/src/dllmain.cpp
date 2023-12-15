#include "dllmain.h"
#include <vector>
#include <cstdlib>
#include "minecraft/src-client/common/client/game/ClientInstance.h"
#include "Mod.h"
#include "AmethystRuntime.h"
#include "amethyst/Log.h"
#include "amethyst/HookManager.h"

AmethystRuntime g_runtime;
HookManager g_hookManager;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Main, NULL, 0, NULL);
    }
    return TRUE;
}

DWORD WINAPI Main() {
    Log::InitializeConsole();

    #ifdef MOD_VERSION
    Log::Info("[AmethystRuntime] AmethystRuntime{}\n", MOD_VERSION);
    #endif

    try {
        g_runtime.LoadMods();
        g_runtime.RunMods();
    }
    catch (std::exception e) {
        Log::Error("[AmethystRuntime] Uncaught Exception: {}\n", e.what());
        ShutdownWait();
        return 1;
    }

    g_runtime.Shutdown();
    ShutdownWait();
    return 0;
}

DWORD __stdcall EjectThread(LPVOID lpParameter) {
    ExitProcess(0);
}

void Shutdown() {
    g_runtime.Shutdown();
    Log::DestroyConsole();
    MH_Uninitialize();

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