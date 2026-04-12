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
            return mHook.ccall<R, QualifiedSelf, Args...>(self, args...);
        }
        else if constexpr (Convention == CallingConvention::StdCall) {
            return mHook.stdcall<R, QualifiedSelf, Args...>(self, args...);
        }
        else if constexpr (Convention == CallingConvention::FastCall) {
            return mHook.fastcall<R, QualifiedSelf, Args...>(self, args...);
        }
        return mHook.thiscall<R, QualifiedSelf, Args...>(self, args...);
    }

    template <CallingConvention Convention = CallingConvention::Default>
    R operator()(QualifiedSelf self, Args... args)
    {
        return call<Convention>(self, args...);
    }
};

template <typename R, typename Self, typename... Args>
class InlineHook<R (Self::*)(Args...) const> {
public:
    using QualifiedSelf = const Self*;
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
            return mHook.ccall<R, QualifiedSelf, Args...>(self, args...);
        }
        else if constexpr (Convention == CallingConvention::StdCall) {
            return mHook.stdcall<R, QualifiedSelf, Args...>(self, args...);
        }
        else if constexpr (Convention == CallingConvention::FastCall) {
            return mHook.fastcall<R, QualifiedSelf, Args...>(self, args...);
        }
        return mHook.thiscall<R, QualifiedSelf, Args...>(self, args...);
    }

    template <CallingConvention Convention = CallingConvention::Default>
    R operator()(QualifiedSelf self, Args... args)
    {
        return call<Convention>(self, args...);
    }
};

template <typename R, typename Self, typename... Args>
class InlineHook<R (Self::*)(Args...) const volatile> {
public:
    using QualifiedSelf = const volatile Self*;
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
            return mHook.ccall<R, QualifiedSelf, Args...>(self, args...);
        }
        else if constexpr (Convention == CallingConvention::StdCall) {
            return mHook.stdcall<R, QualifiedSelf, Args...>(self, args...);
        }
        else if constexpr (Convention == CallingConvention::FastCall) {
            return mHook.fastcall<R, QualifiedSelf, Args...>(self, args...);
        }
        return mHook.thiscall<R, QualifiedSelf, Args...>(self, args...);
    }

    template <CallingConvention Convention = CallingConvention::Default>
    R operator()(QualifiedSelf self, Args... args)
    {
        return call<Convention>(self, args...);
    }
};

template <typename R, typename Self, typename... Args>
class InlineHook<R (Self::*)(Args...)&> {
public:
    using QualifiedSelf = Self*;
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
            return mHook.ccall<R, QualifiedSelf, Args...>(self, args...);
        }
        else if constexpr (Convention == CallingConvention::StdCall) {
            return mHook.stdcall<R, QualifiedSelf, Args...>(self, args...);
        }
        else if constexpr (Convention == CallingConvention::FastCall) {
            return mHook.fastcall<R, QualifiedSelf, Args...>(self, args...);
        }
        return mHook.thiscall<R, QualifiedSelf, Args...>(self, args...);
    }

    template <CallingConvention Convention = CallingConvention::Default>
    R operator()(QualifiedSelf self, Args... args)
    {
        return call<Convention>(self, args...);
    }
};

template <typename R, typename Self, typename... Args>
class InlineHook<R (Self::*)(Args...)&&> {
public:
    using QualifiedSelf = Self*;
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
            return mHook.ccall<R, QualifiedSelf, Args...>(self, args...);
        }
        else if constexpr (Convention == CallingConvention::StdCall) {
            return mHook.stdcall<R, QualifiedSelf, Args...>(self, args...);
        }
        else if constexpr (Convention == CallingConvention::FastCall) {
            return mHook.fastcall<R, QualifiedSelf, Args...>(self, args...);
        }
        return mHook.thiscall<R, QualifiedSelf, Args...>(self, args...);
    }

    template <CallingConvention Convention = CallingConvention::Default>
    R operator()(QualifiedSelf self, Args... args)
    {
        return call<Convention>(self, args...);
    }
};

template <typename R, typename Self, typename... Args>
class InlineHook<R (Self::*)(Args...) const&> {
public:
    using QualifiedSelf = const Self*;
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
            return mHook.ccall<R, QualifiedSelf, Args...>(self, args...);
        }
        else if constexpr (Convention == CallingConvention::StdCall) {
            return mHook.stdcall<R, QualifiedSelf, Args...>(self, args...);
        }
        else if constexpr (Convention == CallingConvention::FastCall) {
            return mHook.fastcall<R, QualifiedSelf, Args...>(self, args...);
        }
        return mHook.thiscall<R, QualifiedSelf, Args...>(self, args...);
    }

    template <CallingConvention Convention = CallingConvention::Default>
    R operator()(QualifiedSelf self, Args... args)
    {
        return call<Convention>(self, args...);
    }
};

template <typename R, typename Self, typename... Args>
class InlineHook<R (Self::*)(Args...) const&&> {
public:
    using QualifiedSelf = const Self*;
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
            return mHook.ccall<R, QualifiedSelf, Args...>(self, args...);
        }
        else if constexpr (Convention == CallingConvention::StdCall) {
            return mHook.stdcall<R, QualifiedSelf, Args...>(self, args...);
        }
        else if constexpr (Convention == CallingConvention::FastCall) {
            return mHook.fastcall<R, QualifiedSelf, Args...>(self, args...);
        }
        return mHook.thiscall<R, QualifiedSelf, Args...>(self, args...);
    }

    template <CallingConvention Convention = CallingConvention::Default>
    R operator()(QualifiedSelf self, Args... args)
    {
        return call<Convention>(self, args...);
    }
};

template <typename R, typename Self, typename... Args>
class InlineHook<R (Self::*)(Args...) const volatile&> {
public:
    using QualifiedSelf = const volatile Self*;
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
            return mHook.ccall<R, QualifiedSelf, Args...>(self, args...);
        }
        else if constexpr (Convention == CallingConvention::StdCall) {
            return mHook.stdcall<R, QualifiedSelf, Args...>(self, args...);
        }
        else if constexpr (Convention == CallingConvention::FastCall) {
            return mHook.fastcall<R, QualifiedSelf, Args...>(self, args...);
        }
        return mHook.thiscall<R, QualifiedSelf, Args...>(self, args...);
    }

    template <CallingConvention Convention = CallingConvention::Default>
    R operator()(QualifiedSelf self, Args... args)
    {
        return call<Convention>(self, args...);
    }
};

template <typename R, typename Self, typename... Args>
class InlineHook<R (Self::*)(Args...) const volatile&&> {
public:
    using QualifiedSelf = const volatile Self*;
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
            return mHook.ccall<R, QualifiedSelf, Args...>(self, args...);
        }
        else if constexpr (Convention == CallingConvention::StdCall) {
            return mHook.stdcall<R, QualifiedSelf, Args...>(self, args...);
        }
        else if constexpr (Convention == CallingConvention::FastCall) {
            return mHook.fastcall<R, QualifiedSelf, Args...>(self, args...);
        }
        return mHook.thiscall<R, QualifiedSelf, Args...>(self, args...);
    }

    template <CallingConvention Convention = CallingConvention::Default>
    R operator()(QualifiedSelf self, Args... args)
    {
        return call<Convention>(self, args...);
    }
};
} // namespace Amethyst