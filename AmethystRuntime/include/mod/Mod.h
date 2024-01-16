#pragma once

#include <amethyst/Log.h>
#include <amethyst/Utility.h>

#include <cstdint>
#include <filesystem>
#include <iostream>
#include <vector>

namespace fs = std::filesystem;

class Mod {
private:
    uint64_t hModule;

public:
    std::string modName;

public:
    Mod(std::string modName);
    intptr_t GetFunction(const char* functionName) const;
    void Shutdown() const;

private:
    fs::path GetTempDll() const;
};