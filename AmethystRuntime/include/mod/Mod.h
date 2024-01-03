#pragma once
#include <Windows.h>
#include <filesystem>
#include <iostream>
#include <shlobj.h>
#include <vector>
#include <amethyst/Utility.h>
#include <amethyst/Log.h>

namespace fs = std::filesystem;

class Mod {
private:
    HMODULE hModule;

public:
    std::string modName;

public:
    Mod(std::string modName);
    FARPROC GetFunction(const char* functionName);
    void Shutdown();

private:
    fs::path GetTempDll();
};