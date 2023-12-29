#pragma once
#include <Windows.h>
#include <shlobj.h>
#include "Utils.h"
#include <filesystem>
#include <iostream>
#include <vector>

namespace fs = std::filesystem;

class Mod {
private:
	HMODULE hModule;

public:
	std::string modName;

public:
	Mod(std::string modName);
	FARPROC GetFunction(const char* funcName);
	void Free();

private:
	fs::path GetTempDll();
};