// AmethystLauncher.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "amethyst/Config.h"
#include "default_config.h"
#include "loader/Loader.h"
#include "loader/PermissionChanger.h"
#include <codecvt>
#include <filesystem>
#include <locale>
namespace fs = std::filesystem;

Config LoadConfig()
{
    std::string amethystFolderPath = GetAmethystPath();

    if (!fs::exists(amethystFolderPath)) {
        Log::Info("[AmethystLauncher] Creating Amethyst folder at {}", amethystFolderPath);

        fs::create_directory(amethystFolderPath);
    }

    std::string configPath = amethystFolderPath + "/config.json";

    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

    if (!fs::exists(configPath)) {
        std::ofstream configFile(configPath);

        if (!configFile) {
            std::string message = fmt::format("[AmethystLauncher] Could not create default config.json at '{}'", configPath);
            ReportIssue(converter.from_bytes(message).c_str());
            std::abort();
        }

        configFile << default_config;

        configFile.close();
    }

    Log::Info("[AmethystLauncher] Loading config from: {}", configPath);

    std::ifstream configFile(configPath);
    if (!configFile.is_open()) {
        std::string message = fmt::format("[AmethystLauncher] Failed to open config.json at '{}'", configPath);
        ReportIssue(converter.from_bytes(message).c_str());
        std::abort();
    }

    // Read into a std::string
    std::stringstream buffer;
    buffer << configFile.rdbuf();
    configFile.close();
    std::string fileContents = buffer.str();
    return Config(fileContents);
}

int main()
{
    if (!AddALLToDirectoryPermissions())
        ReportIssue(L"Failed to add permissions to the Amethyst folder. Amethyst needs admin to do this");

    Config config = LoadConfig();
    ModLoader loader(config);

    loader.InjectRuntime();
}