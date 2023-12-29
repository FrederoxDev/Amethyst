#pragma once
#include "Utils.h"
#include <Windows.h>
#include <filesystem>
#include <iostream>
#include <shlobj.h>
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