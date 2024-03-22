#pragma once
#include "Json.hpp"
#include <Windows.h>
#include <amethyst/Log.h>
#include <amethyst/Utility.h>
#include <filesystem>
#include <iostream>
#include <shlobj.h>
#include <vector>
using json = nlohmann::json;

namespace fs = std::filesystem;

class Mod {
private:
    HMODULE hModule;

public:
    struct MetaData {
        std::string name;
        std::string version;
        std::vector<std::string> author;
    };

public:
    std::string modName;
    MetaData metaData;

public:
    Mod(std::string modName);
    FARPROC GetFunction(const char* functionName);
    void Shutdown();

public:
    static Mod::MetaData GetMetaData(std::string modName);
    static Mod::MetaData ParseMetaData(std::string modName, std::string fileContents);

private:
    fs::path GetTempDll();
};