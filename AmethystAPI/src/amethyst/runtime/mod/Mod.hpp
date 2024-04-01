#pragma once
#include "Json.hpp"
#include <Windows.h>
#include <amethyst/Log.hpp>
#include <amethyst/Utility.hpp>
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
    struct Metadata {
        std::string name;
        std::string version;
        std::vector<std::string> author;
    };

public:
    std::string modName;
    Metadata metadata;

public:
    Mod(std::string modName);
    FARPROC GetFunction(const char* functionName);
    void Shutdown();

public:
    static Mod::Metadata GetMetadata(std::string modName);
    static Mod::Metadata ParseMetadata(std::string modName, std::string fileContents);

private:
    fs::path GetTempDll();
};