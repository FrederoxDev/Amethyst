#include "ModInfo.h"

std::optional<Amethyst::ModInfo> Amethyst::ModInfo::getModInfoFromText(std::string modName, std::string text)
{
    // Parse config.json into json
    json data;

    try {
        data = json::parse(text);
    }
    catch (std::exception e) {
        Log::Warning("Failed to parse mod.json");
        return std::nullopt;
    }

    // Verify all fields are correct in config.json
    if (!data["meta"].is_object()) {
        Log::Warning("Required field \"meta\" should be of type \"object\" in mod.json");
        return std::nullopt;
    }

    if (!data["meta"]["name"].is_string()) {
        Log::Warning("Required field \"name\" in \"meta\" should be of type \"string\" in mod.json");
        return std::nullopt;
    }

    if (!data["meta"]["author"].is_string()) {
        Log::Warning("Required field \"author\" in \"meta\" should be of type \"string\" in mod.json");
        return std::nullopt;
    }

    if (!data["meta"]["version"].is_string()) {
        Log::Warning("Required field \"version\" in \"meta\" should be of type \"string\" in mod.json");
        return std::nullopt;
    }

    // Set values
    ModInfo info;

    info.meta.name = data["meta"]["name"];
    info.meta.author = data["meta"]["author"];
    info.meta.version = data["meta"]["version"];

    return info;
}