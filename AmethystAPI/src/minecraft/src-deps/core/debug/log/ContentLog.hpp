#pragma once
#include <cstdint>
#include "amethyst/Memory.hpp"
#include "ContentLogTypes.hpp"

class ContentLog {
public:
    uintptr_t** vtable;

    // 1.20.72.1 - 48 89 5C 24 ? 48 89 4C 24 ? 57 48 83 EC ? 48 8B F9 48 8D 05 ? ? ? ? 48 89 01 48 89 4C 24 ? 48 83 C1 ? 48 8D 54 24 ? E8 ? ? ? ? 90 48 8D 05 ? ? ? ? 48 89 07 C6 47
    ContentLog();

    template<typename... Strings>
    int Log(bool doNotRepeat, LogLevel logLevel, LogArea logArea, Strings... strings) {
        using function = int (ContentLog::*)(bool, LogLevel, LogArea, Strings...);
        auto func = std::bit_cast<function>(SigScan("44 89 4C 24 ? 48 83 EC"));
        return (this->*func)(doNotRepeat, logLevel, logArea, strings...);
    }
};