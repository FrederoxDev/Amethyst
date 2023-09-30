// dllmain.cpp : Defines the entry point for the DLL application.
#include "dllmain.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Main, NULL, 0, NULL);
    }

    return TRUE;
}

DWORD WINAPI Main() {
    AllocConsole();
    FILE* fp;

    freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONOUT$", "w", stderr);

    MH_STATUS status = MH_Initialize();
    if (status != MH_OK) {
        printf("MH_Initialize: %s\n", MH_StatusToString(status));
        ShutdownWait(fp);
        return 1;
    }

    printf("Minecraft Base Address: %Ix\n", GetMinecraftBaseAddress());

    try {
        ModInitializeHooks();
    }
    catch (std::exception const&) {
        ShutdownWait(fp);
        return 1;
    }

    while (1) {
        Sleep(100);
        if (GetAsyncKeyState(VK_NUMPAD0))
            break;
    }

    Shutdown(fp);
    return 0;
}

DWORD __stdcall EjectThread(LPVOID lpParameter) {
    ExitProcess(0);
}

void Shutdown(FILE* fp) {
    fclose(fp);
    FreeConsole();
    MH_Uninitialize();
    CreateThread(0, 0, EjectThread, 0, 0, 0);
}

void ShutdownWait(FILE* fp) {
    printf("Press Numpad0 to close...\n");

    while (1) {
        Sleep(50);
        if (GetAsyncKeyState(VK_NUMPAD0)) break;
    }

    Shutdown(fp);
}
