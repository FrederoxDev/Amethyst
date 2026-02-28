#pragma once
#include "amethyst-deps/safetyhook.hpp"
#include "amethyst/Log.hpp"
#include "amethyst/Memory.hpp"
#include <unordered_map>
#include <vector>
#include <Core/String/HashedString.hpp>

// #define NO_THROW_HOOK(className, functionName, signature)                                                                  \
// {                                                                                                                      \
//     auto scan = SigScanSafe(signature);                                                                                \
//     if (!scan.has_value())                                                                                             \
//         Log::Warning("[SAFE_HOOK] SigScan failed for {}::{}, signature = {}", #className, #functionName, signature);   \
//     else {                                                                                                             \
//         hookManager->RegisterFunction<&className::functionName>(scan.value());                                         \
//         hookManager->CreateHook<&className::functionName>(_##className##_##functionName, &className##_##functionName); \
//     }                                                                                                                  \
// }

#define HOOK(className, functionName)                                                                               \
{                                                                                                                   \
    hooks.CreateDirectHook<&className::functionName>(_##className##_##functionName, &className##_##functionName); \
}

#define VHOOK(className, functionName, forName)                                                                                  \
{                                                                                                                  \
    hooks.CreateVirtualHook<&className::functionName>(##className::$vtable_for_##forName, _##className##_##functionName, &className##_##functionName); \
}


namespace Amethyst {
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

        template<typename T>
        static consteval uint64_t class_hash() {
            constexpr std::string_view name = __FUNCSIG__;
            return HashedString::computeHash(name);
        }
    };

    class HookManager {
    public:
        HookManager() = default;
        HookManager(const HookManager&) = delete;
        HookManager(HookManager&&) = delete;
        HookManager& operator=(const HookManager&) = delete;
        HookManager& operator=(HookManager&&) = delete;

        template <auto OriginalFn>
        void CreateDirectHook(SafetyHookInline& trampoline, void* hook)
        {
            using FnType = decltype(OriginalFn);
            uintptr_t original_addr = 0;

            if constexpr (std::is_member_function_pointer_v<FnType>) {
                // will cause issues if a virtual function is passed here
                union { FnType fn; uintptr_t addr; } u{};
                u.fn = OriginalFn;
                original_addr = u.addr;
            } 
            else {
                original_addr = std::bit_cast<uintptr_t>(OriginalFn);
            }

            // uintptr_t original_addr = std::bit_cast<uintptr_t>(OriginalFn);
            CreateHookAbsolute(trampoline, original_addr, hook);
        }

        template <auto OriginalFn>
        void CreateVirtualHook(uintptr_t vtable, SafetyHookInline& trampoline, void* hook)
        {
            size_t offset = GetVirtualFunctionOffset<OriginalFn>();
            uintptr_t vtableEntry = reinterpret_cast<uintptr_t*>(vtable)[offset / sizeof(void*)];
            CreateHookAbsolute(trampoline, vtableEntry, hook);
        }

        /**
         * Directly replaces a virtual function in a virtual table
         * CAUTION: This will not work if two mods want to replace the same function. For more compatibility, use HookManager::CreateVirtualHook
         */
        template <auto OriginalFn>
        uintptr_t ReplaceVirtualFunction(uintptr_t vtable, void* newFunction)
        {
            size_t offset = GetVirtualFunctionOffset<OriginalFn>();
            uintptr_t* vtablePtr = reinterpret_cast<uintptr_t*>(vtable);
            uintptr_t& function = vtablePtr[offset / sizeof(void*)];
            uintptr_t original = function;
            DWORD oldProt;
            UnprotectMemory(reinterpret_cast<uintptr_t>(&function), sizeof(uintptr_t), &oldProt);
            function = reinterpret_cast<uintptr_t>(newFunction);
            ProtectMemory(reinterpret_cast<uintptr_t>(&function), sizeof(uintptr_t), oldProt);
            return original;
        }

        // Legacy funcs
        // I'm just trying to figure out if its worth just removing em?

        // template <auto OriginalFn>
        // void CreateHook(SafetyHookInline& trampoline, void* hook)
        // {
        //     constexpr size_t hash = function_id::hash_code<OriginalFn>();

        //     Assert(mFuncHashToOriginalAddress.contains(hash), "[AmethystAPI] '{}' has not registered!", function_id::name<OriginalFn>());

        //     uintptr_t original_addr = mFuncHashToOriginalAddress[hash];
        //     CreateHookAbsolute(trampoline, original_addr, hook);
        // }

        // template <auto Func>
        // void RegisterFunction(std::string_view signature)
        // {
        //     // Converts the function to a unique hashed number
        //     constexpr size_t hash = function_id::hash_code<Func>();

        //     // If the event has not yet been created, make it, else re-use
        //     if (!mFuncHashToOriginalAddress.contains(hash)) {
        //         auto result = SigScanSafe(signature);

        //         Assert(result.has_value(), "Failed to find function: \"{}\"\nUsing signature: \"{}\"", function_id::name<Func>(), signature);

        //         mFuncHashToOriginalAddress[hash] = result.value();
        //     }
        // }

        // template <auto Func>
        // void RegisterFunction(uintptr_t address)
        // {
        //     // Converts the function to a unique hashed number
        //     constexpr size_t hash = function_id::hash_code<Func>();

        //     // If the event has not yet been created, make it, else re-use
        //     if (!mFuncHashToOriginalAddress.contains(hash)) {
        //         mFuncHashToOriginalAddress[hash] = address;
        //     }
        // }


        /**
         * Directly hooks a function with an absolute address
         * CAUTION: This will not work if two mods want to hook the same function. For more compatibility, use HookManager::CreateHook
         */
        void CreateHookAbsolute(SafetyHookInline& safetyHookTrampoline, uintptr_t originalAddress, void* hook)
        {
            safetyHookTrampoline = safetyhook::create_inline((void*)originalAddress, hook);
            mHooks.push_back(&safetyHookTrampoline);
        }

        ~HookManager();
    private:
        std::vector<SafetyHookInline*> mHooks;
        std::unordered_map<size_t, uintptr_t> mFuncHashToOriginalAddress;
        friend class AmethystRuntime;
    };
} // namespace Amethyst