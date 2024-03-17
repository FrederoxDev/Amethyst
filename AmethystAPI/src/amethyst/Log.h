#pragma once
#include <Windows.h>
#include <fmt/color.h>
#include <fmt/core.h>
#include <iostream>

namespace Log {
    void InitializeConsole();
    void DestroyConsole();

    template <typename... T>
    void Info(fmt::format_string<T...> fmt, T&&... args) {
        std::string formatted_string = fmt::format(fmt, std::forward<T>(args)...);
        fmt::print("{}\n", formatted_string);
    }

    template <typename... T>
    void Warning(fmt::format_string<T...> fmt, T&&... args) {
        std::string formatted_string = fmt::format(fmt, std::forward<T>(args)...);
        fmt::print(fg(fmt::rgb(0xf5f556)) | fmt::emphasis::bold, "{}\n", formatted_string);
    }

    template <typename... T>
    void Error(fmt::format_string<T...> fmt, T&&... args) {
        std::string formatted_string = fmt::format(fmt, std::forward<T>(args)...);
        fmt::print(fg(fmt::rgb(0xf55762)) | fmt::emphasis::bold, "{}\n", formatted_string);
    }

    template <typename... T>
    inline void _Assert(const char* function, int line, fmt::format_string<T...> fmt, T&&... args)
    {
        std::string formatted_string = fmt::format(fmt, std::forward<T>(args)...);
        formatted_string += fmt::format("\n\tin: {}, line: {}", function, line);
        throw std::exception(formatted_string.c_str());
    }
     
}; // namespace Log

#define Assert(...) Log::_Assert(__FUNCTION__, __LINE__, __VA_ARGS__)
