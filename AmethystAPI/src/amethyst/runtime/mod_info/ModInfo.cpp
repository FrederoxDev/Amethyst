#include "ModInfo.h"

std::optional<Amethyst::ModInfo> Amethyst::ModInfo::getModInfoFromText(std::string modName, std::string text)
{
    // Parse config.json into json
    json data;

    try {
        data = json::parse(text);
    }
    catch (std::exception e) {
        Log::Error("[AmethystRuntime] Failed to parse mod.json, for {}\n Error: {}", modName, e.what());
        throw std::exception();
    }

    // Verify all fields are correct in config.json
    if (!data["meta"].is_object()) {
        Log::Error("[AmethystRuntime] Required field \"meta\" should be of type \"object\" in mod.json, for {}", modName);
        throw std::exception();
    }

    if (!data["meta"]["name"].is_string()) {
        Log::Error("[AmethystRuntime] Required field \"name\" in \"meta\" should be of type \"string\" in mod.json, for {}", modName);
        throw std::exception();
    }

    std::vector<std::string> authors = {};

    if (data["meta"]["author"].is_string()) {
        authors.push_back(data["meta"]["author"]);
    }
    else if (data["meta"]["author"].is_array()) {
        for (const auto& element : data["meta"]["author"]) {
            if (!element.is_string()) {
                Log::Error("[AmethystRuntime] Array \"author\" in \"meta\" should only contain fields of type \"string\" in mod.json, for {}", modName);
                throw std::exception();
            }
            else {
                authors.push_back(element);
            }
        }
    }
    else {
        Log::Error("[AmethystRuntime] Required field \"author\" in \"meta\" should be of type \"string\" | \"string[]\" in mod.json, for {}", modName);
        throw std::exception();
    }

    if (!data["meta"]["version"].is_string()) {
        Log::Error("[AmethystRuntime] Required field \"version\" in \"meta\" should be of type \"string\" in mod.json, for {}", modName);
        throw std::exception();
    }

    // Set values
    ModInfo info;

    info.meta.name = data["meta"]["name"];
    info.meta.author = authors;
    info.meta.version = data["meta"]["version"];

    return info;
}