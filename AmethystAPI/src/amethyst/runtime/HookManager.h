#pragma once
#include "amethyst-deps/safetyhook.hpp"
#include "amethyst/Log.h"
#include "amethyst/Memory.h"
#include <unordered_map>
#include <vector>

class HookManager {
public:
     template <typename OriginalFn>
     void CreateHook(OriginalFn function, SafetyHookInline& trampoline, void* hook)
     {
         size_t hash = typeid(function).hash_code();

         if (mFuncHashToOriginalAddress.find(hash) == mFuncHashToOriginalAddress.end())
         {
             Log::Error("[AmethystAPI] '{}' has not registered!", typeid(function).name());
             throw std::exception();
         }

         uintptr_t original_addr = mFuncHashToOriginalAddress[hash];
         CreateHookAbsolute(trampoline, original_addr, hook);
     }
    
    /**
     * Directly hooks a function with an absolute address
     * CAUTION: This will not work if two mods want to hook the same function. For more compatibility, use HookManager::CreateHook
     */
    void CreateHookAbsolute(SafetyHookInline& safetyHookTrampoline, uintptr_t originalAddress, void* hook) {
        safetyHookTrampoline = safetyhook::create_inline((void*)originalAddress, hook);
        mHooks.push_back(&safetyHookTrampoline);
    }

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
    std::vector<SafetyHookInline*> mHooks;
    std::unordered_map<size_t, uintptr_t> mFuncHashToOriginalAddress;
};