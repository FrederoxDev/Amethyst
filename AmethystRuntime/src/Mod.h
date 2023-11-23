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
	const char* mod_name;

public:
	Mod(const char* mod_name);
	FARPROC GetFunction(const char* func_name);
	void Free();

private:
	fs::path GetTempDll();
};