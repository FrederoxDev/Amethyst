#include "amethyst/HookManager.h"

/*
Disables any hooks and un-caches any stored addresses
*/
void HookManager::Shutdown()
{
    for (auto it = mHooks.rbegin(); it != mHooks.rend(); ++it) {
        auto* hook = *it;
        *hook = {};
    }

    mHooks.clear();
    mFuncHashToOriginalAddress.clear();
}

//void HookManager::CreateHookAbsolute(uintptr_t targetAddress, void* detour, void** original)
//{
//    LPVOID original_addr = reinterpret_cast<LPVOID>(targetAddress);
//    MH_STATUS status;
//
//    status = MH_CreateHook(original_addr, detour, original);
//    if (status != MH_OK) {
//        Log::Error("MH_CreateHook failed: Reason: {}", MH_StatusToString(status));
//        throw std::exception();
//    }
//
//    status = MH_EnableHook(original_addr);
//    if (status != MH_OK) {
//        Log::Error("MH_EnableHook failed: Reason: {}", MH_StatusToString(status));
//        throw std::exception();
//    }
//
//    m_hooks.push_back(original_addr);
//}