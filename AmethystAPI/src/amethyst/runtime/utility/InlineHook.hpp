#pragma once
#include <amethyst/runtime/HookManager.hpp>

template <typename>
struct function_traits;

template <typename Ret, typename... Args>
struct function_traits<Ret(Args...)> {
    using return_type = Ret;
    using args_tuple = std::tuple<Args...>;
    static constexpr std::size_t arity = sizeof...(Args);
};

namespace Amethyst {
template <typename T>
// Helper to disambiguate overloaded member functions
constexpr T OverloadCast(T t) { 
    return t; 
}

#define OVERLOAD_CAST(klass, fn, ret, ...) \
    Amethyst::OverloadCast<ret (klass::*)(__VA_ARGS__)>(klass::fn)

enum class CallingConvention : uint8_t {
    Default,
    CDecl,
    StdCall,
    ThisCall,
    FastCall
};

namespace detail {
    /// Forward-declared single-inheritance proxy: MSVC encodes member fn ptrs
    /// to a `__single_inheritance` class as a 1-word code address. We cast
    /// `Self*` to `Proxy*` at the call site so MSVC emits member-function ABI
    /// (RCX=this, RDX=sret) regardless of `Self`'s real inheritance shape.
    class __single_inheritance Proxy;

    /// Convert a raw code address into a non-virtual member function pointer
    /// of the single-inheritance Proxy class.
    template <typename ProxyMemFn>
    inline ProxyMemFn AddrToProxyMemFn(uintptr_t addr) noexcept {
        static_assert(std::is_member_function_pointer_v<ProxyMemFn>,
            "AddrToProxyMemFn requires a member function pointer type");
        static_assert(sizeof(ProxyMemFn) == sizeof(uintptr_t),
            "Proxy MFP must be a single code address; ensure Proxy is forward-declared "
            "with __single_inheritance");
        union { uintptr_t a; ProxyMemFn m; } u{};
        u.a = addr;
        return u.m;
    }
}

template <typename T>
class VSwapHook {
    static_assert(sizeof(T) == 0, "VSwapHook<T> is not supported!");
};

template <typename R, typename Self, typename... Args>
class VSwapHook<R(Self::*)(Args...)> {
public:
    using QualifiedSelf = Self*;
    uintptr_t mOriginal = 0;

    operator bool() const noexcept { return mOriginal != 0; }

    R call(QualifiedSelf self, Args... args)
    {
        Assert(mOriginal != 0, "Attempted to call a VSwapHook that was not installed!");
        using ProxyMemFn = R (detail::Proxy::*)(Args...);
        auto mfn = detail::AddrToProxyMemFn<ProxyMemFn>(mOriginal);
        auto* p = reinterpret_cast<detail::Proxy*>(
            const_cast<std::remove_cv_t<Self>*>(self));
        return (p->*mfn)(std::forward<Args>(args)...);
    }

    R operator()(QualifiedSelf self, Args... args)
    {
        return call(self, std::forward<Args>(args)...);
    }
};

template <typename R, typename Self, typename... Args>
class VSwapHook<R(Self::*)(Args...) const> {
public:
    using QualifiedSelf = const Self*;
    uintptr_t mOriginal = 0;

    operator bool() const noexcept { return mOriginal != 0; }

    R call(QualifiedSelf self, Args... args)
    {
        Assert(mOriginal != 0, "Attempted to call a VSwapHook that was not installed!");
        using ProxyMemFn = R (detail::Proxy::*)(Args...);
        auto mfn = detail::AddrToProxyMemFn<ProxyMemFn>(mOriginal);
        auto* p = reinterpret_cast<detail::Proxy*>(
            const_cast<std::remove_cv_t<Self>*>(self));
        return (p->*mfn)(std::forward<Args>(args)...);
    }

    R operator()(QualifiedSelf self, Args... args)
    {
        return call(self, std::forward<Args>(args)...);
    }
};

template <typename T>
class InlineHook {
    static_assert(sizeof(T) == 0, "InlineHook<T> is not supported!");
};

template <typename R, typename... Args>
class InlineHook<R(*)(Args...)> {
public:
    SafetyHookInline mHook;

    InlineHook() = default;
    InlineHook(const InlineHook&) = delete;
    InlineHook(InlineHook&&) noexcept = default;
    InlineHook(SafetyHookInline&& hook) noexcept
        : mHook(std::move(hook)) {}

    InlineHook& operator=(const InlineHook&) = delete;
    InlineHook& operator=(InlineHook&&) noexcept = default;

    operator bool() const noexcept 
    {
        return mHook.operator bool();
    }

    operator const SafetyHookInline&() const noexcept 
    {
        return mHook;
    }

    operator SafetyHookInline&()
    {
        return mHook;
    }

    template<CallingConvention Convention = CallingConvention::Default>
    R call(Args... args)
    {
        Assert(mHook.operator bool(), "Attempted to call an InlineHook that was invalid!");
        if constexpr (Convention == CallingConvention::CDecl) {
            return mHook.ccall<R, Args...>(std::forward<Args>(args)...);
        } else if constexpr (Convention == CallingConvention::StdCall) {
            return mHook.stdcall<R, Args...>(std::forward<Args>(args)...);
        } else if constexpr (Convention == CallingConvention::ThisCall) {
            return mHook.thiscall<R, Args...>(std::forward<Args>(args)...);
        } else if constexpr (Convention == CallingConvention::FastCall) {
            return mHook.fastcall<R, Args...>(std::forward<Args>(args)...);
        }
        return mHook.call<R, Args...>(std::forward<Args>(args)...);
    }

    template <CallingConvention Convention = CallingConvention::Default>
    R operator()(Args... args)
    {
        return call<Convention>(std::forward<Args>(args)...);
    }
};

template <typename R, typename Self, typename... Args>
class InlineHook<R(Self::*)(Args...)> {
public:
    using QualifiedSelf = Self*;
    using MemFn = R (Self::*)(Args...);
    SafetyHookInline mHook;

    InlineHook() = default;
    InlineHook(const InlineHook&) = delete;
    InlineHook(InlineHook&&) noexcept = default;
    InlineHook(SafetyHookInline&& hook) noexcept
        : mHook(std::move(hook)) {}

    InlineHook& operator=(const InlineHook&) = delete;
    InlineHook& operator=(InlineHook&&) noexcept = default;

    operator bool() const noexcept
    {
        return mHook.operator bool();
    }

    operator const SafetyHookInline&() const noexcept
    {
        return mHook;
    }

    operator SafetyHookInline&()
    {
        return mHook;
    }

    template <CallingConvention Convention = CallingConvention::Default>
    R call(QualifiedSelf self, Args... args)
    {
        Assert(mHook.operator bool(), "Attempted to call an InlineHook that was invalid!");
        if constexpr (Convention == CallingConvention::CDecl) {
            return mHook.ccall<R, QualifiedSelf, Args...>(self, std::forward<Args>(args)...);
        }
        else if constexpr (Convention == CallingConvention::StdCall) {
            return mHook.stdcall<R, QualifiedSelf, Args...>(self, std::forward<Args>(args)...);
        }
        else if constexpr (Convention == CallingConvention::FastCall) {
            return mHook.fastcall<R, QualifiedSelf, Args...>(self, std::forward<Args>(args)...);
        }
        using ProxyMemFn = R (detail::Proxy::*)(Args...);
        auto mfn = detail::AddrToProxyMemFn<ProxyMemFn>(mHook.trampoline().address());
        auto* p = reinterpret_cast<detail::Proxy*>(
            const_cast<std::remove_cv_t<Self>*>(self));
        return (p->*mfn)(std::forward<Args>(args)...);
    }

    template <CallingConvention Convention = CallingConvention::Default>
    R operator()(QualifiedSelf self, Args... args)
    {
        return call<Convention>(self, std::forward<Args>(args)...);
    }
};

template <typename R, typename Self, typename... Args>
class InlineHook<R (Self::*)(Args...) const> {
public:
    using QualifiedSelf = const Self*;
    using MemFn = R (Self::*)(Args...) const;
    SafetyHookInline mHook;

    InlineHook() = default;
    InlineHook(const InlineHook&) = delete;
    InlineHook(InlineHook&&) noexcept = default;
    InlineHook(SafetyHookInline&& hook) noexcept
        : mHook(std::move(hook)) {}

    InlineHook& operator=(const InlineHook&) = delete;
    InlineHook& operator=(InlineHook&&) noexcept = default;

    operator bool() const noexcept
    {
        return mHook.operator bool();
    }

    operator const SafetyHookInline&() const noexcept
    {
        return mHook;
    }

    operator SafetyHookInline&()
    {
        return mHook;
    }

    template <CallingConvention Convention = CallingConvention::Default>
    R call(QualifiedSelf self, Args... args)
    {
        Assert(mHook.operator bool(), "Attempted to call an InlineHook that was invalid!");
        if constexpr (Convention == CallingConvention::CDecl) {
            return mHook.ccall<R, QualifiedSelf, Args...>(self, std::forward<Args>(args)...);
        }
        else if constexpr (Convention == CallingConvention::StdCall) {
            return mHook.stdcall<R, QualifiedSelf, Args...>(self, std::forward<Args>(args)...);
        }
        else if constexpr (Convention == CallingConvention::FastCall) {
            return mHook.fastcall<R, QualifiedSelf, Args...>(self, std::forward<Args>(args)...);
        }
        using ProxyMemFn = R (detail::Proxy::*)(Args...);
        auto mfn = detail::AddrToProxyMemFn<ProxyMemFn>(mHook.trampoline().address());
        auto* p = reinterpret_cast<detail::Proxy*>(
            const_cast<std::remove_cv_t<Self>*>(self));
        return (p->*mfn)(std::forward<Args>(args)...);
    }

    template <CallingConvention Convention = CallingConvention::Default>
    R operator()(QualifiedSelf self, Args... args)
    {
        return call<Convention>(self, std::forward<Args>(args)...);
    }
};

template <typename R, typename Self, typename... Args>
class InlineHook<R (Self::*)(Args...) const volatile> {
public:
    using QualifiedSelf = const volatile Self*;
    using MemFn = R (Self::*)(Args...) const volatile;
    SafetyHookInline mHook;

    InlineHook() = default;
    InlineHook(const InlineHook&) = delete;
    InlineHook(InlineHook&&) noexcept = default;
    InlineHook(SafetyHookInline&& hook) noexcept
        : mHook(std::move(hook)) {}

    InlineHook& operator=(const InlineHook&) = delete;
    InlineHook& operator=(InlineHook&&) noexcept = default;

    operator bool() const noexcept
    {
        return mHook.operator bool();
    }

    operator const SafetyHookInline&() const noexcept
    {
        return mHook;
    }

    operator SafetyHookInline&()
    {
        return mHook;
    }

    template <CallingConvention Convention = CallingConvention::Default>
    R call(QualifiedSelf self, Args... args)
    {
        Assert(mHook.operator bool(), "Attempted to call an InlineHook that was invalid!");
        if constexpr (Convention == CallingConvention::CDecl) {
            return mHook.ccall<R, QualifiedSelf, Args...>(self, std::forward<Args>(args)...);
        }
        else if constexpr (Convention == CallingConvention::StdCall) {
            return mHook.stdcall<R, QualifiedSelf, Args...>(self, std::forward<Args>(args)...);
        }
        else if constexpr (Convention == CallingConvention::FastCall) {
            return mHook.fastcall<R, QualifiedSelf, Args...>(self, std::forward<Args>(args)...);
        }
        using ProxyMemFn = R (detail::Proxy::*)(Args...);
        auto mfn = detail::AddrToProxyMemFn<ProxyMemFn>(mHook.trampoline().address());
        auto* p = reinterpret_cast<detail::Proxy*>(
            const_cast<std::remove_cv_t<Self>*>(self));
        return (p->*mfn)(std::forward<Args>(args)...);
    }

    template <CallingConvention Convention = CallingConvention::Default>
    R operator()(QualifiedSelf self, Args... args)
    {
        return call<Convention>(self, std::forward<Args>(args)...);
    }
};

template <typename R, typename Self, typename... Args>
class InlineHook<R (Self::*)(Args...)&> {
public:
    using QualifiedSelf = Self*;
    using MemFn = R (Self::*)(Args...) &;
    SafetyHookInline mHook;

    InlineHook() = default;
    InlineHook(const InlineHook&) = delete;
    InlineHook(InlineHook&&) noexcept = default;
    InlineHook(SafetyHookInline&& hook) noexcept
        : mHook(std::move(hook)) {}

    InlineHook& operator=(const InlineHook&) = delete;
    InlineHook& operator=(InlineHook&&) noexcept = default;

    operator bool() const noexcept
    {
        return mHook.operator bool();
    }

    operator const SafetyHookInline&() const noexcept
    {
        return mHook;
    }

    operator SafetyHookInline&()
    {
        return mHook;
    }

    template <CallingConvention Convention = CallingConvention::Default>
    R call(QualifiedSelf self, Args... args)
    {
        Assert(mHook.operator bool(), "Attempted to call an InlineHook that was invalid!");
        if constexpr (Convention == CallingConvention::CDecl) {
            return mHook.ccall<R, QualifiedSelf, Args...>(self, std::forward<Args>(args)...);
        }
        else if constexpr (Convention == CallingConvention::StdCall) {
            return mHook.stdcall<R, QualifiedSelf, Args...>(self, std::forward<Args>(args)...);
        }
        else if constexpr (Convention == CallingConvention::FastCall) {
            return mHook.fastcall<R, QualifiedSelf, Args...>(self, std::forward<Args>(args)...);
        }
        using ProxyMemFn = R (detail::Proxy::*)(Args...);
        auto mfn = detail::AddrToProxyMemFn<ProxyMemFn>(mHook.trampoline().address());
        auto* p = reinterpret_cast<detail::Proxy*>(
            const_cast<std::remove_cv_t<Self>*>(self));
        return (p->*mfn)(std::forward<Args>(args)...);
    }

    template <CallingConvention Convention = CallingConvention::Default>
    R operator()(QualifiedSelf self, Args... args)
    {
        return call<Convention>(self, std::forward<Args>(args)...);
    }
};

template <typename R, typename Self, typename... Args>
class InlineHook<R (Self::*)(Args...)&&> {
public:
    using QualifiedSelf = Self*;
    using MemFn = R (Self::*)(Args...) &&;
    SafetyHookInline mHook;

    InlineHook() = default;
    InlineHook(const InlineHook&) = delete;
    InlineHook(InlineHook&&) noexcept = default;
    InlineHook(SafetyHookInline&& hook) noexcept
        : mHook(std::move(hook)) {}

    InlineHook& operator=(const InlineHook&) = delete;
    InlineHook& operator=(InlineHook&&) noexcept = default;

    operator bool() const noexcept
    {
        return mHook.operator bool();
    }

    operator const SafetyHookInline&() const noexcept
    {
        return mHook;
    }

    operator SafetyHookInline&()
    {
        return mHook;
    }

    template <CallingConvention Convention = CallingConvention::Default>
    R call(QualifiedSelf self, Args... args)
    {
        Assert(mHook.operator bool(), "Attempted to call an InlineHook that was invalid!");
        if constexpr (Convention == CallingConvention::CDecl) {
            return mHook.ccall<R, QualifiedSelf, Args...>(self, std::forward<Args>(args)...);
        }
        else if constexpr (Convention == CallingConvention::StdCall) {
            return mHook.stdcall<R, QualifiedSelf, Args...>(self, std::forward<Args>(args)...);
        }
        else if constexpr (Convention == CallingConvention::FastCall) {
            return mHook.fastcall<R, QualifiedSelf, Args...>(self, std::forward<Args>(args)...);
        }
        using ProxyMemFn = R (detail::Proxy::*)(Args...);
        auto mfn = detail::AddrToProxyMemFn<ProxyMemFn>(mHook.trampoline().address());
        auto* p = reinterpret_cast<detail::Proxy*>(
            const_cast<std::remove_cv_t<Self>*>(self));
        return (p->*mfn)(std::forward<Args>(args)...);
    }

    template <CallingConvention Convention = CallingConvention::Default>
    R operator()(QualifiedSelf self, Args... args)
    {
        return call<Convention>(self, std::forward<Args>(args)...);
    }
};

template <typename R, typename Self, typename... Args>
class InlineHook<R (Self::*)(Args...) const&> {
public:
    using QualifiedSelf = const Self*;
    using MemFn = R (Self::*)(Args...) const &;
    SafetyHookInline mHook;

    InlineHook() = default;
    InlineHook(const InlineHook&) = delete;
    InlineHook(InlineHook&&) noexcept = default;
    InlineHook(SafetyHookInline&& hook) noexcept
        : mHook(std::move(hook)) {}

    InlineHook& operator=(const InlineHook&) = delete;
    InlineHook& operator=(InlineHook&&) noexcept = default;

    operator bool() const noexcept
    {
        return mHook.operator bool();
    }

    operator const SafetyHookInline&() const noexcept
    {
        return mHook;
    }

    operator SafetyHookInline&()
    {
        return mHook;
    }

    template <CallingConvention Convention = CallingConvention::Default>
    R call(QualifiedSelf self, Args... args)
    {
        Assert(mHook.operator bool(), "Attempted to call an InlineHook that was invalid!");
        if constexpr (Convention == CallingConvention::CDecl) {
            return mHook.ccall<R, QualifiedSelf, Args...>(self, std::forward<Args>(args)...);
        }
        else if constexpr (Convention == CallingConvention::StdCall) {
            return mHook.stdcall<R, QualifiedSelf, Args...>(self, std::forward<Args>(args)...);
        }
        else if constexpr (Convention == CallingConvention::FastCall) {
            return mHook.fastcall<R, QualifiedSelf, Args...>(self, std::forward<Args>(args)...);
        }
        using ProxyMemFn = R (detail::Proxy::*)(Args...);
        auto mfn = detail::AddrToProxyMemFn<ProxyMemFn>(mHook.trampoline().address());
        auto* p = reinterpret_cast<detail::Proxy*>(
            const_cast<std::remove_cv_t<Self>*>(self));
        return (p->*mfn)(std::forward<Args>(args)...);
    }

    template <CallingConvention Convention = CallingConvention::Default>
    R operator()(QualifiedSelf self, Args... args)
    {
        return call<Convention>(self, std::forward<Args>(args)...);
    }
};

template <typename R, typename Self, typename... Args>
class InlineHook<R (Self::*)(Args...) const&&> {
public:
    using QualifiedSelf = const Self*;
    using MemFn = R (Self::*)(Args...) const &&;
    SafetyHookInline mHook;

    InlineHook() = default;
    InlineHook(const InlineHook&) = delete;
    InlineHook(InlineHook&&) noexcept = default;
    InlineHook(SafetyHookInline&& hook) noexcept
        : mHook(std::move(hook)) {}

    InlineHook& operator=(const InlineHook&) = delete;
    InlineHook& operator=(InlineHook&&) noexcept = default;

    operator bool() const noexcept
    {
        return mHook.operator bool();
    }

    operator const SafetyHookInline&() const noexcept
    {
        return mHook;
    }

    operator SafetyHookInline&()
    {
        return mHook;
    }

    template <CallingConvention Convention = CallingConvention::Default>
    R call(QualifiedSelf self, Args... args)
    {
        Assert(mHook.operator bool(), "Attempted to call an InlineHook that was invalid!");
        if constexpr (Convention == CallingConvention::CDecl) {
            return mHook.ccall<R, QualifiedSelf, Args...>(self, std::forward<Args>(args)...);
        }
        else if constexpr (Convention == CallingConvention::StdCall) {
            return mHook.stdcall<R, QualifiedSelf, Args...>(self, std::forward<Args>(args)...);
        }
        else if constexpr (Convention == CallingConvention::FastCall) {
            return mHook.fastcall<R, QualifiedSelf, Args...>(self, std::forward<Args>(args)...);
        }
        using ProxyMemFn = R (detail::Proxy::*)(Args...);
        auto mfn = detail::AddrToProxyMemFn<ProxyMemFn>(mHook.trampoline().address());
        auto* p = reinterpret_cast<detail::Proxy*>(
            const_cast<std::remove_cv_t<Self>*>(self));
        return (p->*mfn)(std::forward<Args>(args)...);
    }

    template <CallingConvention Convention = CallingConvention::Default>
    R operator()(QualifiedSelf self, Args... args)
    {
        return call<Convention>(self, std::forward<Args>(args)...);
    }
};

template <typename R, typename Self, typename... Args>
class InlineHook<R (Self::*)(Args...) const volatile&> {
public:
    using QualifiedSelf = const volatile Self*;
    using MemFn = R (Self::*)(Args...) const volatile &;
    SafetyHookInline mHook;

    InlineHook() = default;
    InlineHook(const InlineHook&) = delete;
    InlineHook(InlineHook&&) noexcept = default;
    InlineHook(SafetyHookInline&& hook) noexcept
        : mHook(std::move(hook)) {}

    InlineHook& operator=(const InlineHook&) = delete;
    InlineHook& operator=(InlineHook&&) noexcept = default;

    operator bool() const noexcept
    {
        return mHook.operator bool();
    }

    operator const SafetyHookInline&() const noexcept
    {
        return mHook;
    }

    operator SafetyHookInline&()
    {
        return mHook;
    }

    template <CallingConvention Convention = CallingConvention::Default>
    R call(QualifiedSelf self, Args... args)
    {
        Assert(mHook.operator bool(), "Attempted to call an InlineHook that was invalid!");
        if constexpr (Convention == CallingConvention::CDecl) {
            return mHook.ccall<R, QualifiedSelf, Args...>(self, std::forward<Args>(args)...);
        }
        else if constexpr (Convention == CallingConvention::StdCall) {
            return mHook.stdcall<R, QualifiedSelf, Args...>(self, std::forward<Args>(args)...);
        }
        else if constexpr (Convention == CallingConvention::FastCall) {
            return mHook.fastcall<R, QualifiedSelf, Args...>(self, std::forward<Args>(args)...);
        }
        using ProxyMemFn = R (detail::Proxy::*)(Args...);
        auto mfn = detail::AddrToProxyMemFn<ProxyMemFn>(mHook.trampoline().address());
        auto* p = reinterpret_cast<detail::Proxy*>(
            const_cast<std::remove_cv_t<Self>*>(self));
        return (p->*mfn)(std::forward<Args>(args)...);
    }

    template <CallingConvention Convention = CallingConvention::Default>
    R operator()(QualifiedSelf self, Args... args)
    {
        return call<Convention>(self, std::forward<Args>(args)...);
    }
};

template <typename R, typename Self, typename... Args>
class InlineHook<R (Self::*)(Args...) const volatile&&> {
public:
    using QualifiedSelf = const volatile Self*;
    using MemFn = R (Self::*)(Args...) const volatile &&;
    SafetyHookInline mHook;

    InlineHook() = default;
    InlineHook(const InlineHook&) = delete;
    InlineHook(InlineHook&&) noexcept = default;
    InlineHook(SafetyHookInline&& hook) noexcept
        : mHook(std::move(hook)) {}

    InlineHook& operator=(const InlineHook&) = delete;
    InlineHook& operator=(InlineHook&&) noexcept = default;

    operator bool() const noexcept
    {
        return mHook.operator bool();
    }

    operator const SafetyHookInline&() const noexcept
    {
        return mHook;
    }

    operator SafetyHookInline&()
    {
        return mHook;
    }

    template <CallingConvention Convention = CallingConvention::Default>
    R call(QualifiedSelf self, Args... args)
    {
        Assert(mHook.operator bool(), "Attempted to call an InlineHook that was invalid!");
        if constexpr (Convention == CallingConvention::CDecl) {
            return mHook.ccall<R, QualifiedSelf, Args...>(self, std::forward<Args>(args)...);
        }
        else if constexpr (Convention == CallingConvention::StdCall) {
            return mHook.stdcall<R, QualifiedSelf, Args...>(self, std::forward<Args>(args)...);
        }
        else if constexpr (Convention == CallingConvention::FastCall) {
            return mHook.fastcall<R, QualifiedSelf, Args...>(self, std::forward<Args>(args)...);
        }
        using ProxyMemFn = R (detail::Proxy::*)(Args...);
        auto mfn = detail::AddrToProxyMemFn<ProxyMemFn>(mHook.trampoline().address());
        auto* p = reinterpret_cast<detail::Proxy*>(
            const_cast<std::remove_cv_t<Self>*>(self));
        return (p->*mfn)(std::forward<Args>(args)...);
    }

    template <CallingConvention Convention = CallingConvention::Default>
    R operator()(QualifiedSelf self, Args... args)
    {
        return call<Convention>(self, std::forward<Args>(args)...);
    }
};
} // namespace Amethyst