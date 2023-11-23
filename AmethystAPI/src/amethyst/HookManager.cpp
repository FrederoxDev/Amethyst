#include "amethyst/HookManager.h"

HookManager::HookManager() {}

void HookManager::CreateHook(uintptr_t targetAddress, void* detour, void** original) {
    LPVOID original_addr = reinterpret_cast<LPVOID>(targetAddress);

    MH_STATUS status;

    status = MH_CreateHook(original_addr, detour, original);
    if (status != MH_OK) {
        Log::Error("Create: Reason: {}\n", MH_StatusToString(status));
        throw std::exception();
    }

    status = MH_EnableHook(original_addr);
    if (status != MH_OK) {
        Log::Error("Enable: Reason: {}\n", MH_StatusToString(status));
        throw std::exception();
    }
}

void HookManager::Shutdown() {
    for each(auto hook in m_hooks) {
        MH_DisableHook(hook);
        MH_RemoveHook(hook);        
    }

    m_hooks.clear();
}