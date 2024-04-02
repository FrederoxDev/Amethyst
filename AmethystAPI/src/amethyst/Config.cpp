#include "amethyst/Config.hpp"

Config::Config()
{
}

Config::Config(std::string& text)
{
    // Parse config.json into json
    json data;

    try {
        data = json::parse(text);
    }
    catch (std::exception e) {
        Log::Error("Failed to parse config.json");
        throw e;
    }

    // Verify all fields are correct in config.json
    if (!data["runtime"].is_string()) {
        throw std::exception("Required field \"runtime\" should be of type \"string\" in config.json");
    }

    if (!data["mods"].is_array()) {
        throw std::exception("Required field \"mods\" should be of type \"string[]\" in config.json");
    }

    if (!data["developer_mode"].is_boolean()) {
        throw std::exception("Required field \"developer_mode\" should be of type \"boolean\" in config.json");
    }

    for (const auto& element : data["mods"]) {
        if (!element.is_string()) {
            throw std::exception("Array \"mods\" in config.json should only contain strings");
        }
    }

    // Set values
    this->injectedMod = data["runtime"];
    this->mods = data["mods"];
    this->promptDebugger = data["developer_mode"];
}