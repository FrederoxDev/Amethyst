// dllmain.cpp : Defines the entry point for the DLL application.
#include "dllmain.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Main, NULL, 0, NULL);
    }

    return TRUE;
}

bool MemCompare(const char* data, const char* sig, const char* mask) {
    for (; *mask; ++mask, ++data, ++sig) {
        if (*mask == 'x' && *data != *sig) {
            return false;
        }
    }

    return true;
}

uintptr_t Zenova_Sigscan(const char* sig, const char* mask) {
    uintptr_t i = GetMinecraftBaseAddress();
    uintptr_t size = i + GetMinecraftSize() - std::strlen(mask);

    for (size_t i = 0; i < size; ++i) {
        uintptr_t iaddr = SlideAddress(i);
        if (MemCompare(reinterpret_cast<const char*>(iaddr), sig, mask)) {
            return iaddr;
        }
    }

    return 0;
}

DWORD WINAPI Main() {
    Log::InitializeConsole();
    Log::Info("Minecraft Base Address: 0x{:x}\n", GetMinecraftBaseAddress());
    Log::Info("Minecraft Size: 0x{:x}\n", GetMinecraftSize());

    auto start_time = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 5; i++) {
        uintptr_t res = Zenova_Sigscan("\x48\x89\x5c\x24\x10\x48\x89\x74\x24\x18\x48\x89\x7c\x24\x20\x55\x41\x54\x41\x55\x41\x56\x41\x57\x48\x8d\x6c\x24\xc9\x48\x81\xec\x0\x1\x0\x0\x48\x8b\x5\x00\x00\x00\x00\x48\x33\xc4\x48\x89\x45\x2f\x41", "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxxxxxxx");
        Log::Info("0x{:x}", res);
    }
    Log::Info("\n");
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    Log::Info("Zenova_Sigscan 5 total time: {}ms\n", duration.count());
    Log::Info("  Average time: {}ms\n\n", (float)duration.count() / 5);

    start_time = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 5; i++) {
        SigScan("48 89 5C 24 10 48 89 74 24 18 48 89 7C 24 20 55 41 54 41 55 41 56 41 57 48 8D 6C 24 C9 48 81 EC 00 01 00 00 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 2F 41");
    }
    Log::Info("\n");
    end_time = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    Log::Info("Freddie_Sigscan ran 5 total time: {}ms\n", duration.count());
    Log::Info("  Average time: {}ms\n\n", (float)duration.count() / 5);


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
