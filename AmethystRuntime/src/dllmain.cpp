#include "dllmain.h"
#include "Log.h"
#include "Hook.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Main, NULL, 0, NULL);
    }

    return TRUE;
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

    // HMODULE hModDLL = LoadLibrary("C:\\Users\\Freddie\\Documents\\AmethystMods\\VoiceChat\\x64\\Release\\VoiceChat.dll");
    // if (hModDLL == NULL) {
    //     DWORD error = GetLastError();

    //     if (error == 0x5) {
    //         Log::Error("Incorrect permissions on VoiceChat.dll: Error 0x5\n");
    //     }
    //     else {
    //         Log::Error("Failed to load VoiceChat.dll: Error 0x{:x}\n", GetLastError());
    //     }

    //     ShutdownWait();
    //     return 1;
    // }

    // ModInitializeHooks modInitializeHooks = reinterpret_cast<ModInitializeHooks>(
    //     GetProcAddress(hModDLL, "ModInitializeHooks")
    // );

    // modInitializeHooks();

    /*try {
        ModInitializeHooks();
    }
    catch (std::exception const&) {
        ShutdownWait();
        return 1;
    }*/

    // Todo: Hook into world tick or something
    while (true) {
        Sleep(50); // 1/20th second
        // ModTick();
        if (GetAsyncKeyState(VK_NUMPAD0)) break;
    }

    // FreeLibrary(hModDLL);
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