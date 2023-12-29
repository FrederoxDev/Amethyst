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
    std::string mod_name;

public:
    Mod(std::string mod_name);
    FARPROC GetFunction(const char* func_name);
    void Free();

private:
    fs::path GetTempDll();
};