// AmethystLauncher.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "loader/Loader.h"
#include "amethyst/Config.h"
#include <filesystem>
#include <locale>
#include <codecvt>
#include "loader/PermissionChanger.h"
namespace fs = std::filesystem;

Config LoadConfig() {
    std::string configPath = GetAmethystUWPFolder() + "config.json";
    Log::Info("[AmethystRuntime] Loading config from: {}\n", configPath);

    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

    if (!fs::exists(configPath)) {
        std::string message = fmt::format("[AmethystLauncher] Could not find config.json at '{}'\n", configPath);
        ReportIssue(converter.from_bytes(message).c_str());
        std::abort();
    }

    std::ifstream configFile(configPath);
    if (!configFile.is_open()) {
        std::string message = fmt::format("[AmethystLauncher] Failed to open config.json at '{}'\n", configPath);
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

int main() {
    if (!AddALLToDirectoryPermissions())
        ReportIssue(L"Failed to add permissions to the Amethyst folder. Amethyst needs admin to do this");

    /*Config config = LoadConfig();
    ModLoader loader(config);

	loader.InjectRuntime();*/
}