#pragma once
#include "MinHook.h"
#include "amethyst/Log.h"
#include "amethyst/Memory.h"
#include <unordered_map>
#include <vector>

class HookManager {
public:
    template <typename Func>
    void CreateHook(Func function, void* detour, void** original)
    {
        size_t hash = typeid(function).hash_code();

        if (mFuncHashToOriginalAddress.find(hash) == mFuncHashToOriginalAddress.end()) 
        {
            Log::Error("[AmethystAPI] '{}' has not registered!", typeid(function).name());
            throw std::exception();
        }

        LPVOID original_addr = reinterpret_cast<LPVOID>(mFuncHashToOriginalAddress[hash]);
        CreateHookAbsolute(original_addr, detour, original);
    }

    void CreateHookAbsolute(uintptr_t targetAddress, void* detour, void** original);

    template <typename Func>
    void RegisterFunction(Func function, std::string_view signature)
    {
        // Converts the function to a unique hashed number
        size_t hash = typeid(function).hash_code();

        // If the event has not yet been created, make it, else re-use
        if (mFuncHashToOriginalAddress.find(hash) == mFuncHashToOriginalAddress.end()) 
        {
            mFuncHashToOriginalAddress[hash] = SigScan(signature);
        }
    }

    template <typename Func>
    void RegisterFunction(Func function, uintptr_t address)
    {
        // Converts the function to a unique hashed number
        size_t hash = typeid(function).hash_code();

        // If the event has not yet been created, make it, else re-use
        if (mFuncHashToOriginalAddress.find(hash) == mFuncHashToOriginalAddress.end()) 
        {
            mFuncHashToOriginalAddress[hash] = address;
        }
    }

    void Shutdown();

private:
    std::vector<LPVOID> m_hooks;
    std::unordered_map<size_t, uintptr_t> mFuncHashToOriginalAddress;
};