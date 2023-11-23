#include "amethyst/HookManager.h"

HookManager::HookManager() {}

void HookManager::CreateHook(uintptr_t targetAddress, void* detour, void* original) {
    LPVOID address = reinterpret_cast<LPVOID>(targetAddress);

    MH_STATUS status = MH_CreateHook(address, detour, reinterpret_cast<LPVOID*>(&original));

    // When loaded for the first time MH will not be initialized
    if (status == MH_ERROR_NOT_INITIALIZED) {
        status = MH_Initialize();

        if (status != MH_OK) {
            Log::Error("MH_Initialize failed! Reason: {}\n", MH_StatusToString(status));
            throw std::exception();
        }

        // Re-attempt the hook
        status = MH_CreateHook(address, detour, reinterpret_cast<LPVOID*>(&original));
    }

    // Creating the hook failed, MH is initialized at this point
    if (status != MH_OK) {
        Log::Error("MH_CreateHook failed! Reason: {}\n", MH_StatusToString(status));
        throw std::exception();
    }

    status = MH_EnableHook(address);
    if (status != MH_OK) {
        Log::Error("MH_EnableHook failed! Reason: {}\n", MH_StatusToString(status));
        throw std::exception();
    }
}