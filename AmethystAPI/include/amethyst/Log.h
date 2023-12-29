#pragma once
#include <fmt/core.h>
#include <fmt/color.h>
#include <Windows.h>
#include <iostream>

namespace Log
{
	void InitializeConsole();
	void DestroyConsole();

	template<typename... T>
	void Info(fmt::format_string<T...> fmt, T&&... args) {
		std::string formatted_string = fmt::format(fmt, std::forward<T>(args)...);
		fmt::print("{}\n", formatted_string);
	}

	template<typename... T>
	void Warning(fmt::format_string<T...> fmt, T&&... args) {
		std::string formatted_string = fmt::format(fmt, std::forward<T>(args)...);
		fmt::print(fg(fmt::rgb(0xf5f556)) | fmt::emphasis::bold, "{}\n", formatted_string);
	}

	template<typename... T>
	void Error(fmt::format_string<T...> fmt, T&&... args) {
		std::string formatted_string = fmt::format(fmt, std::forward<T>(args)...);
		fmt::print(fg(fmt::rgb(0xf55762)) | fmt::emphasis::bold, "{}\n", formatted_string);
	}
};