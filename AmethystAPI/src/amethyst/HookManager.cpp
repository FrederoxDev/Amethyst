#include "amethyst/HookManager.h"

void HookManager::Shutdown()
{
    for (auto hook : m_hooks) {
        MH_STATUS status;

        status = MH_DisableHook(hook);
        if (status != MH_OK) {
            Log::Error("MH_DisableHook failed: Reason: {}", MH_StatusToString(status));
            throw std::exception();
        }

        status = MH_RemoveHook(hook);
        if (status != MH_OK) {
            Log::Error("MH_RemoveHook failed: Reason: {}", MH_StatusToString(status));
            throw std::exception();
        }
    }

    m_hooks.clear();
    mFuncHashToOriginalAddress.clear();
}

/*
    Creates a hook with an absolute address
*/
void HookManager::CreateHook(uintptr_t targetAddress, void* detour, void** original)
{
    LPVOID original_addr = reinterpret_cast<LPVOID>(targetAddress);
    MH_STATUS status;

    status = MH_CreateHook(original_addr, detour, original);
    if (status != MH_OK) {
        Log::Error("MH_CreateHook failed: Reason: {}", MH_StatusToString(status));
        throw std::exception();
    }

    status = MH_EnableHook(original_addr);
    if (status != MH_OK) {
        Log::Error("MH_EnableHook failed: Reason: {}", MH_StatusToString(status));
        throw std::exception();
    }

    m_hooks.push_back(original_addr);
}