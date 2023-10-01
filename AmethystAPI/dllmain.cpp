// dllmain.cpp : Defines the entry point for the DLL application.
#include "dllmain.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Main, NULL, 0, NULL);
    }

    return TRUE;
}

DWORD WINAPI Main() {
    Log::InitializeConsole();
    Log::Info("Minecraft Base Address: 0x{:x}\n", GetMinecraftBaseAddress());

    MH_STATUS status = MH_Initialize();
    if (status != MH_OK) {
        Log::Error("MH_Initialize failed! Reason: {}\n", MH_StatusToString(status));
        ShutdownWait();
        return 1;
    }

    try {
        ModInitializeHooks();
    }
    catch (std::exception const&) {
        ShutdownWait();
        return 1;
    }

    while (true) {
        Sleep(10);
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
