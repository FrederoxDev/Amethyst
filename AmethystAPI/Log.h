#pragma once
#include <fmt/core.h>
#include <fmt/color.h>
#include <Windows.h>

namespace Log
{
	void InitializeConsole();
	void DestroyConsole();

	template <typename... Args>
	void Info(const char* format, const Args&... args) {
		fmt::print(format, args...);
	}

	template <typename... Args>
	void Error(const char* format, const Args&... args) {
		fmt::print(fg(fmt::rgb(0xf55762)) | fmt::emphasis::bold, format, args...);
	}
};

