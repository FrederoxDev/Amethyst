#include "dllmain.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Main, NULL, 0, NULL);
    }
    return TRUE;
}

DWORD WINAPI Main()
{
    Log::InitializeConsole();

    // Create an instance of AmethystRuntime and invoke it to start
    AmethystRuntime* runtime = AmethystRuntime::getInstance();

    try {
        runtime->Start();
    }
    catch (std::exception& exception) {
        Log::Error("[AmethystRuntime] Uncaught Exception: {}", exception.what());
        ShutdownWait();
        return 1;
    }

    ShutdownWait();
    return 0;
}

DWORD __stdcall EjectThread(LPVOID lpParameter)
{
    ExitProcess(0);
}

void Shutdown()
{
    AmethystRuntime* runtime = AmethystRuntime::getInstance();
    runtime->Shutdown();

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