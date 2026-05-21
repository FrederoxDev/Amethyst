#pragma once
#include "Utility.hpp"
#include <iostream>
#include <fstream>
#include <format>
#include <intrin.h>
#include <utility>
#include <mutex>

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>

namespace Log {
    void InitializeConsole();
    void DestroyConsole();
    void HideConsole();
    std::string GetModName();
    std::string GetThreadName();

    void WriteToFile(const std::string& message);
    void InitializeFileLogging();
    void ShutdownFileLogging();

    constexpr const char* RESET   = "\033[0m";
    constexpr const char* YELLOW  = "\033[1;33m";
    constexpr const char* RED     = "\033[1;31m";
    constexpr const char* GRAY = "\033[38;5;245m";

    template <typename... T>
    void Info(const std::format_string<T...> fmt, T&&... args) {
        std::string formatted_string = std::format(fmt, std::forward<T>(args)...);
        formatted_string = std::format("[{}] [{}] {}", GetThreadName(), GetModName(), formatted_string);
        std::cout << formatted_string << std::endl;
        WriteToFile(formatted_string);
    }

    template <typename... T>
    void Warning(const std::format_string<T...> fmt, T&&... args) {
        std::string formatted_string = std::format(fmt, std::forward<T>(args)...);
        formatted_string = std::format("[{}] [{}] [WARN] {}", GetThreadName(), GetModName(), formatted_string);
        std::cout << YELLOW << formatted_string << RESET << std::endl;
        WriteToFile(formatted_string);
    }

    template <typename... T>
    void Error(const std::format_string<T...> fmt, T&&... args) {
        std::string formatted_string = std::format(fmt, std::forward<T>(args)...);
        formatted_string = std::format("[{}] [{}] [ERROR] {}", GetThreadName(), GetModName(), formatted_string);
        std::cerr << RED << formatted_string << RESET << std::endl;
        WriteToFile(formatted_string);
    }

    template <typename... T>
    [[noreturn]]
    inline void _AssertFail(const char* function, int line, const std::format_string<T...> fmt, T&&... args)
    {
        std::string formatted_string = std::format(fmt, std::forward<T>(args)...);
        formatted_string += std::format("\n\tin: {}, line: {}", function, line);
        Log::Error("{}", formatted_string);

        __debugbreak();

        throw std::runtime_error(formatted_string);
    }

    template <typename... T>
    inline void _Assert(bool condition, const char* function, int line, const std::format_string<T...> fmt, T&&... args)
    {
        if (condition) return;
        _AssertFail(function, line, fmt, std::forward<T>(args)...);
		std::unreachable();
    }
}; // namespace Log

#ifdef AMETHYST_OBFUSCATE
#define Assert(condition, ...) Log::_Assert(condition, "", __LINE__, __VA_ARGS__)
#define AssertFail(...) Log::_AssertFail("", __LINE__, __VA_ARGS__)
#else
#define Assert(condition, ...) Log::_Assert(condition, __FUNCTION__, __LINE__, __VA_ARGS__)
#define AssertFail(...) Log::_AssertFail(__FUNCTION__, __LINE__, __VA_ARGS__)
#endif