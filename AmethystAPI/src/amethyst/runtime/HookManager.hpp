#pragma once
#include "amethyst-deps/safetyhook.hpp"
#include "amethyst/Log.hpp"
#include "amethyst/Memory.hpp"
#include <unordered_map>
#include <vector>
#include <Core/String/StringHash.hpp>

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

/// Hook a non-static member fn (overloaded or not) or a static fn.
/// Detour must be named `<className>_<functionName>`, trampoline `_<className>_<functionName>`.
/// For overloads, the detour's signature picks the matching overload of the original via PickOriginal.
#define HOOK(className, functionName)                                                                                                  \
{                                                                                                                                       \
    hooks.CreateDirectHook<                                                                                                            \
        ::Amethyst::detail::PickOriginal(&className::functionName,                                                                     \
            static_cast<decltype(&className##_##functionName)>(nullptr)),                                                              \
        &className##_##functionName>(_##className##_##functionName);                                                                   \
}

#define VHOOK(className, functionName, vtable)                                                                                          \
{                                                                                                                                       \
    hooks.CreateVirtualHook<                                                                                                           \
        ::Amethyst::detail::PickOriginal(&className::functionName,                                                                     \
            static_cast<decltype(&className##_##functionName)>(nullptr)),                                                              \
        &className##_##functionName>(vtable, _##className##_##functionName);                                                           \
}

#define HOOK_DIRECT_VIRTUAL(className, functionName)                                                                                   \
{                                                                                                                                       \
    hooks.CreateDirectHookAt<                                                                                                          \
        ::Amethyst::detail::PickOriginal(&className::functionName,                                                                     \
            static_cast<decltype(&className##_##functionName)>(nullptr)),                                                              \
        &className##_##functionName>(                                                                                                  \
            _##className##_##functionName,                                                                                             \
            std::bit_cast<uintptr_t>(::Amethyst::detail::PickOriginal(                                                                 \
                &className::$direct_##functionName,                                                                                    \
                static_cast<decltype(&className##_##functionName)>(nullptr))));                                                        \
}

/// For overloaded member fns where you have MULTIPLE detours sharing one MC name.
/// `detourSym` is the unique detour symbol; trampoline must be named `_<detourSym>`.
/// Example: HOOK_NAMED(LoopbackPacketSender, sendToClient, LoopbackPacketSender_sendToClientUEIC);
#define HOOK_NAMED(className, functionName, detourSym)                                                                                 \
{                                                                                                                                       \
    hooks.CreateDirectHook<                                                                                                            \
        ::Amethyst::detail::PickOriginal(&className::functionName,                                                                     \
            static_cast<decltype(&detourSym)>(nullptr)),                                                                               \
        &detourSym>(_##detourSym);                                                                                                     \
}

#define VHOOK_NAMED(className, functionName, vtable, detourSym)                                                                        \
{                                                                                                                                       \
    hooks.CreateVirtualHook<                                                                                                           \
        ::Amethyst::detail::PickOriginal(&className::functionName,                                                                     \
            static_cast<decltype(&detourSym)>(nullptr)),                                                                               \
        &detourSym>(vtable, _##detourSym);                                                                                             \
}

#define HOOK_DIRECT_VIRTUAL_NAMED(className, functionName, detourSym)                                                                  \
{                                                                                                                                       \
    hooks.CreateDirectHookAt<                                                                                                          \
        ::Amethyst::detail::PickOriginal(&className::functionName,                                                                     \
            static_cast<decltype(&detourSym)>(nullptr)),                                                                               \
        &detourSym>(                                                                                                                    \
            _##detourSym,                                                                                                              \
            std::bit_cast<uintptr_t>(::Amethyst::detail::PickOriginal(                                                                 \
                &className::$direct_##functionName,                                                                                    \
                static_cast<decltype(&detourSym)>(nullptr))));                                                                         \
}

#define VSWAP(className, functionName, vtable)                                                                                          \
{                                                                                                                                       \
    _##className##_##functionName.mOriginal = hooks.CreateVirtualSwap<                                                                 \
        ::Amethyst::detail::PickOriginal(&className::functionName,                                                                     \
            static_cast<decltype(&className##_##functionName)>(nullptr)),                                                              \
        &className##_##functionName>(vtable);                                                                                          \
}

#define VSWAP_NAMED(className, functionName, vtable, detourSym)                                                                        \
{                                                                                                                                       \
    _##detourSym.mOriginal = hooks.CreateVirtualSwap<                                                                                  \
        ::Amethyst::detail::PickOriginal(&className::functionName,                                                                     \
            static_cast<decltype(&detourSym)>(nullptr)),                                                                               \
        &detourSym>(vtable);                                                                                                           \
}


namespace Amethyst {
    /**
     * HookShim resolves an MSVC x64 ABI mismatch.
     *
     * MSVC compiles a free function returning a non-trivially-copyable type with
     * "free-function sret ABI" — the hidden return-buffer pointer goes in RCX
     * (args slide right). MSVC compiles a member function with "member-function
     * sret ABI" — `this` in RCX, sret in RDX, args in R8/R9/stack.
     *
     * When safetyhook patches a member function's prologue and we install a
     * free-function detour as the destination, the call site emits member-fn
     * ABI but our detour reads free-fn ABI. The args slide one register and
     * `self` arrives as the sret buffer. Symptom: `self->vftable` points at
     * uninitialized memory, fields read junk, AV inside MC's body after the
     * trampoline.
     *
     * Fix: install a tiny shim that is itself a non-virtual member function on
     * a `__single_inheritance` class. MSVC emits the shim with member-fn ABI
     * (matching the call site). The shim body forwards to the user's free-fn
     * detour as a normal intra-DLL call, where MSVC reshuffles registers
     * automatically. ABI gap absorbed.
     */
    template <auto OrigFn, auto UserDetour, typename FnSig = decltype(OrigFn)>
    struct HookShim;

    template <auto OrigFn, auto UserDetour, typename R, typename Self, typename... Args>
    struct __single_inheritance HookShim<OrigFn, UserDetour, R (Self::*)(Args...)> {
        R Trampoline(Args... args) {
            return UserDetour(reinterpret_cast<Self*>(this), std::forward<Args>(args)...);
        }
    };

    template <auto OrigFn, auto UserDetour, typename R, typename Self, typename... Args>
    struct __single_inheritance HookShim<OrigFn, UserDetour, R (Self::*)(Args...) const> {
        R Trampoline(Args... args) const {
            return UserDetour(reinterpret_cast<const Self*>(this), std::forward<Args>(args)...);
        }
    };

    template <auto OrigFn, auto UserDetour, typename R, typename Self, typename... Args>
    struct __single_inheritance HookShim<OrigFn, UserDetour, R (Self::*)(Args...) const volatile> {
        R Trampoline(Args... args) const volatile {
            return UserDetour(reinterpret_cast<const volatile Self*>(this), std::forward<Args>(args)...);
        }
    };

    namespace detail {
        /// Pick the right overload of `&Class::fn` based on the detour's signature.
        /// The macro passes a typed `nullptr` of the detour's type as the second
        /// argument; overload resolution forces the matching `&Class::fn` overload.
        ///
        /// Provided overloads cover the common cases:
        ///  - non-cv member function
        ///  - const member function
        ///  - const volatile member function
        ///  - free / static function (detour and original share the same type)
        ///
        /// `&` / `&&` ref-qualified MC member functions are rare enough to require
        /// manual `CreateDirectHook` if encountered — add an overload here if they
        /// come up in practice.

        template <typename R, typename Self, typename... Args>
        constexpr auto PickOriginal(R (Self::*orig)(Args...), R(*)(Self*, Args...)) {
            return orig;
        }

        template <typename R, typename Self, typename... Args>
        constexpr auto PickOriginal(R (Self::*orig)(Args...) const, R(*)(const Self*, Args...)) {
            return orig;
        }

        template <typename R, typename Self, typename... Args>
        constexpr auto PickOriginal(R (Self::*orig)(Args...) const volatile, R(*)(const volatile Self*, Args...)) {
            return orig;
        }

        template <typename R, typename... Args>
        constexpr auto PickOriginal(R(*orig)(Args...), R(*)(Args...)) {
            return orig;
        }
    }

    /// Resolve a user detour to a code address with member-fn ABI.
    /// For member-fn-pointer originals: install the HookShim's Trampoline so
    /// MSVC emits the right register layout. For free-fn originals: the user's
    /// detour is already correct — install it directly.
    template <auto OrigFn, auto UserDetour>
    inline void* ResolveDetourAddress() {
        using OrigType = decltype(OrigFn);
        if constexpr (std::is_member_function_pointer_v<OrigType>) {
            using Shim = HookShim<OrigFn, UserDetour>;
            using ShimMemFn = decltype(&Shim::Trampoline);
            static_assert(sizeof(ShimMemFn) == sizeof(uintptr_t),
                "HookShim member fn ptr is not a single code address — __single_inheritance failed");
            union { ShimMemFn fn; uintptr_t addr; } u{};
            u.fn = &Shim::Trampoline;
            return reinterpret_cast<void*>(u.addr);
        }
        else {
            return reinterpret_cast<void*>(UserDetour);
        }
    }

    class function_id {
    public:
        template <auto Fn>
        static consteval uint64_t hash_code()
        {
            return HashedString::computeHash(name<Fn>());
        }

        template <auto Fn>
        static consteval std::string_view name() {
#ifdef AMETHYST_OBFUSCATE
            return "<obfuscated>";
#else
#  if defined(__clang__)
            // clang's __PRETTY_FUNCTION__ shape: "... name() [Fn = &Foo::bar]"
            constexpr std::string_view funcSig = __PRETTY_FUNCTION__;
            constexpr std::string_view prefix = "[Fn = ";
            constexpr std::string_view suffix = "]";
            constexpr std::size_t begin = funcSig.find(prefix);
            constexpr std::size_t end = funcSig.rfind(suffix[0]);
#  else
            // MSVC's __FUNCSIG__ shape: "... function_id::name<&Foo::bar>(void)"
            constexpr std::string_view funcSig = __FUNCSIG__;
            constexpr std::string_view prefix = "function_id::name<";
            constexpr std::string_view suffix = ">";
            constexpr std::size_t begin = funcSig.find(prefix);
            constexpr std::size_t end = funcSig.rfind(suffix[0]);
#  endif
            static_assert(begin != std::string_view::npos);
            static_assert(end != std::string_view::npos);
            return funcSig.substr(begin + prefix.size(), end - begin - prefix.size());
#endif
        }

        template<typename T>
        static consteval uint64_t class_hash() {
#ifdef AMETHYST_OBFUSCATE
            return 0;
#else
            constexpr std::string_view name = __FUNCSIG__;
            return HashedString::computeHash(name);
#endif
        }
    };

    class HookManager {
    public:
        HookManager() = default;
        HookManager(const HookManager&) = delete;
        HookManager(HookManager&&) = delete;
        HookManager& operator=(const HookManager&) = delete;
        HookManager& operator=(HookManager&&) = delete;

        template <auto OriginalFn, auto UserDetour>
        void CreateDirectHook(SafetyHookInline& trampoline)
        {
            using FnType = decltype(OriginalFn);
            uintptr_t original_addr = 0;

            if constexpr (std::is_member_function_pointer_v<FnType>) {
                union { FnType fn; uintptr_t addr; } u{};
                u.fn = OriginalFn;
                original_addr = u.addr;
            }
            else {
                original_addr = std::bit_cast<uintptr_t>(OriginalFn);
            }

            CreateDirectHookAt<OriginalFn, UserDetour>(trampoline, original_addr);
        }

        template <auto OriginalFn, auto UserDetour>
        void CreateDirectHookAt(SafetyHookInline& trampoline, uintptr_t original_addr)
        {
            constexpr std::string_view name = function_id::name<OriginalFn>();
            if (original_addr == 0) {
                Log::Error("[HOOK] Failed to resolve address for '{}' (got nullptr). Are imports resolved?", name);
                return;
            }

            void* hook = ResolveDetourAddress<OriginalFn, UserDetour>();
            CreateHookAbsolute(trampoline, original_addr, hook);
        }

        template <auto OriginalFn, auto UserDetour>
        void CreateVirtualHook(uintptr_t vtable, SafetyHookInline& trampoline)
        {
            constexpr std::string_view name = function_id::name<OriginalFn>();

            if (vtable == 0) {
                Log::Error("[VHOOK] vtable pointer is null for '{}'. Are imports resolved?", name);
                return;
            }

            size_t offset = GetVirtualFunctionOffset<OriginalFn>();
            if (offset == 0) {
                Log::Error("[VHOOK] Failed to get vtable offset for '{}'. Is it actually virtual?", name);
                return;
            }

            size_t index = offset / sizeof(void*);
            uintptr_t vtableEntry = reinterpret_cast<uintptr_t*>(vtable)[index];

            if (vtableEntry == 0) {
                Log::Error("[VHOOK] vtable[{}] is null for '{}' (vtable at 0x{:x})", index, name, vtable);
                return;
            }

            void* hook = ResolveDetourAddress<OriginalFn, UserDetour>();
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

        /**
         * Vtable-slot swap (the ICF-immune alternative to CreateVirtualHook).
         * Writes the HookShim's Trampoline address into the vtable slot, returns
         * the previous slot value (the real function address) so the caller can
         * invoke the original through a VSwapHook<> wrapper.
         *
         * Trade-off vs CreateVirtualHook: VSWAP only redirects calls that go
         * through this particular vtable, so two mods can't both VSWAP the same
         * slot — the second one wins and the first becomes dead. For trivial
         * function bodies (single-instruction getters, etc.) this is the only
         * safe option because the linker folds them with unrelated functions
         * and an inline body patch would redirect those too.
         */
        template <auto OriginalFn, auto UserDetour>
        uintptr_t CreateVirtualSwap(uintptr_t vtable)
        {
            constexpr std::string_view name = function_id::name<OriginalFn>();
            if (vtable == 0) {
                Log::Error("[VSWAP] vtable pointer is null for '{}'. Are imports resolved?", name);
                return 0;
            }
            void* shimAddr = ResolveDetourAddress<OriginalFn, UserDetour>();
            return ReplaceVirtualFunction<OriginalFn>(vtable, shimAddr);
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
