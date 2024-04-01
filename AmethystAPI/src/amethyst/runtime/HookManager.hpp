#pragma once
#include "amethyst-deps/safetyhook.hpp"
#include "amethyst/Log.hpp"
#include "amethyst/Memory.hpp"
#include "minecraft/src-deps/core/string/StringHash.hpp"
#include <unordered_map>
#include <vector>

class function_id {
public:
    template <auto Fn>
    static consteval uint64_t hash_code()
    {
        return HashedString::computeHash(name<Fn>());
    }

    template <auto Fn>
    static consteval std::string_view name() {
        constexpr std::string_view funcSig = __FUNCSIG__;
        constexpr std::string_view prefix = "function_id::name<";
        constexpr std::size_t begin = funcSig.find("function_id::name<");
        constexpr std::size_t end = funcSig.rfind('>');
        static_assert(begin != std::string_view::npos);
        static_assert(end != std::string_view::npos);
        return funcSig.substr(begin + prefix.size(), end - begin - prefix.size());
    }
};

class HookManager {
public:
    template <auto OriginalFn>
    void CreateHook(SafetyHookInline& trampoline, void* hook)
    {
        constexpr size_t hash = function_id::hash_code<OriginalFn>();

        if (!mFuncHashToOriginalAddress.contains(hash)) {
            Assert("[AmethystAPI] '{}' has not registered!", function_id::name<OriginalFn>());
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

    template <auto Func>
    void RegisterFunction(std::string_view signature)
    {
        // Converts the function to a unique hashed number
        constexpr size_t hash = function_id::hash_code<Func>();

        // If the event has not yet been created, make it, else re-use
        if (!mFuncHashToOriginalAddress.contains(hash)) {
            auto result = SigScanSafe(signature);

            if (!result.has_value()) {
                Assert("Failed to find function: \"{}\"\nUsing signature: \"{}\"", function_id::name<Func>(), signature);
            }

            mFuncHashToOriginalAddress[hash] = result.value();
        }
    }

    template <auto Func>
    void RegisterFunction(uintptr_t address)
    {
        // Converts the function to a unique hashed number
        constexpr size_t hash = function_id::hash_code<Func>();

        // If the event has not yet been created, make it, else re-use
        if (!mFuncHashToOriginalAddress.contains(hash)) {
            mFuncHashToOriginalAddress[hash] = address;
        }
    }

    void Shutdown();

private:
    std::vector<SafetyHookInline*> mHooks;
    std::unordered_map<size_t, uintptr_t> mFuncHashToOriginalAddress;
};