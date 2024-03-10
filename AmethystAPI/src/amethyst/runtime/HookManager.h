#pragma once
#include "amethyst-deps/safetyhook.hpp"
#include "amethyst/Log.h"
#include "amethyst/Memory.h"
#include "minecraft/src-deps/core/string/StringHash.h"
#include <unordered_map>
#include <vector>

class function_id {
public:
    template <auto Fn>
    static uint64_t hash_code()
    {
        HashedString hashed(__FUNCSIG__);
        return hashed.getHash();
    }

    template <auto Fn>
    static std::string name() 
    {
        std::string stringified = std::string(__FUNCSIG__);
        std::string startReplace = std::string("function_id::name<");

        size_t startPos = stringified.find(startReplace);

        if (startPos != std::string::npos) {
            stringified = stringified.substr(startPos + startReplace.length());
        }

        if (stringified.size() >= 7) {
            stringified.erase(stringified.size() - 7);
        }

        return stringified;
    }
};

class HookManager {
public:
    template <typename OriginalFn>
    void CreateHook(OriginalFn function, SafetyHookInline& trampoline, void* hook)
    {
        size_t hash = function_id::template hash_code<OriginalFn>();

        if (mFuncHashToOriginalAddress.find(hash) == mFuncHashToOriginalAddress.end()) {
            // Log::Error("[AmethystAPI] '{}' has not registered!", typeid(function).name());
            throw std::exception();
        }

        uintptr_t original_addr = mFuncHashToOriginalAddress[hash];
        CreateHookAbsolute(trampoline, original_addr, hook);
    }

    /**
     * Directly hooks a function with an absolute address
     * CAUTION: This will not work if two mods want to hook the same function. For more compatibility, use HookManager::CreateHook
     */
    void CreateHookAbsolute(SafetyHookInline& safetyHookTrampoline, uintptr_t originalAddress, void* hook)
    {
        safetyHookTrampoline = safetyhook::create_inline((void*)originalAddress, hook);
        mHooks.push_back(&safetyHookTrampoline);
    }

    template <typename Func>
    void RegisterFunction(Func function, std::string_view signature)
    {
        // Converts the function to a unique hashed number
        size_t hash = function_id::hash_code<Func>();

        // If the event has not yet been created, make it, else re-use
        if (mFuncHashToOriginalAddress.find(hash) == mFuncHashToOriginalAddress.end()) {
            auto result = SigScanSafe(signature);

            if (!result.has_value()) {
                std::string error = fmt::format("Failed to find function: \"{}\"\nUsing signature: \"{}\"", typeid(function).name(), signature);
                throw std::exception(error.c_str());
            }

            mFuncHashToOriginalAddress[hash] = result.value();
        }
    }

    template <typename Func>
    void RegisterFunction(Func function, uintptr_t address)
    {
        // Converts the function to a unique hashed number
        size_t hash = function_id::hash_code<Func>();

        // If the event has not yet been created, make it, else re-use
        if (mFuncHashToOriginalAddress.find(hash) == mFuncHashToOriginalAddress.end()) {
            mFuncHashToOriginalAddress[hash] = address;
        }
    }

    void Shutdown();

private:
    std::vector<SafetyHookInline*> mHooks;
    std::unordered_map<size_t, uintptr_t> mFuncHashToOriginalAddress;
};