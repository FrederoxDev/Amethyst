#include "amethyst/Config.hpp"
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <sstream>

namespace {
json LoadProfilesJson()
{
    const char* appdata = std::getenv("APPDATA");
    Assert(appdata != nullptr, "APPDATA environment variable is not set");

    fs::path profilesPath = fs::path(appdata) / "Amethyst" / "Launcher" / "Profiles" / "profiles.json";
    Assert(fs::exists(profilesPath), "profiles.json could not be found at '{}'", profilesPath.string());

    std::ifstream profilesFile(profilesPath);
    Assert(profilesFile.is_open(), "Failed to open profiles.json at '{}'", profilesPath.string());

    std::stringstream buffer;
    buffer << profilesFile.rdbuf();

    try {
        return json::parse(buffer.str());
    }
    catch (...) {
        Assert(false, "Failed to parse profiles.json");
        return json::array();
    }
}

json ResolveSelectedProfile(const json& launcherConfig)
{
    json profiles = LoadProfilesJson();
    Assert(profiles.is_array(), "profiles.json should be an array");
    Assert(!profiles.empty(), "profiles.json does not contain any profiles");

    if (launcherConfig.contains("selected_profile_uuid") && launcherConfig["selected_profile_uuid"].is_string()) {
        const auto selectedUuid = launcherConfig["selected_profile_uuid"].get<std::string>();
        for (const auto& profile : profiles) {
            if (!profile.is_object() || !profile.contains("uuid") || !profile["uuid"].is_string())
                continue;

            if (profile["uuid"].get<std::string>() == selectedUuid)
                return profile;
        }
    }

    size_t selectedProfileIndex = 0;
    if (launcherConfig.contains("selected_profile") && launcherConfig["selected_profile"].is_number_integer()) {
        auto index = launcherConfig["selected_profile"].get<int>();
        if (index >= 0)
            selectedProfileIndex = static_cast<size_t>(index);
    }

    if (selectedProfileIndex >= profiles.size())
        selectedProfileIndex = 0;

    return profiles[selectedProfileIndex];
}
}

Config::Config(std::string& text)
{
    // Parse config.json into json
    json data;

    try {
        data = json::parse(text);
    }
    catch (std::exception e) {
        Assert(false, "Failed to parse config file 'launcher_config.json'");
    }

    Assert(data["developer_mode"].is_boolean(), "Required field \"developer_mode\" should be of type \"boolean\" in config.json");

    const auto selectedProfile = ResolveSelectedProfile(data);
    Assert(selectedProfile.is_object(), "Selected profile is not a valid object");
    Assert(selectedProfile.contains("runtime") && selectedProfile["runtime"].is_string(),
        "Selected profile field \"runtime\" should be of type \"string\"");
    Assert(selectedProfile.contains("mods") && selectedProfile["mods"].is_array(),
        "Selected profile field \"mods\" should be of type \"string[]\"");

    for (const auto& element : selectedProfile["mods"]) {
        Assert(element.is_string(), "Selected profile array \"mods\" should only contain strings");
    }

    this->injectedMod = selectedProfile["runtime"];
    this->mods = selectedProfile["mods"];
    this->promptDebugger = data["developer_mode"];
}