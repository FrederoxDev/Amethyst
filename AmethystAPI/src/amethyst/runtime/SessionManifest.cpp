#include "amethyst/runtime/SessionManifest.hpp"

#include "Json.hpp"
#include "amethyst/Log.hpp"

#include <algorithm>
#include <cwctype>
#include <fstream>
#include <sstream>

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>

using json = nlohmann::json;

namespace Amethyst {
namespace {
bool SamePath(const fs::path& a, const fs::path& b)
{
    std::error_code ec;
    if (fs::equivalent(a, b, ec) && !ec) return true;

    auto normalise = [](const fs::path& path) {
        std::wstring text = path.lexically_normal().wstring();
        while (!text.empty() && (text.back() == L'\\' || text.back() == L'/')) text.pop_back();
        std::transform(text.begin(), text.end(), text.begin(), ::towlower);
        return text;
    };
    return normalise(a) == normalise(b);
}

/*
 * The build this process was launched from. The proxy matches the manifest against its own module
 * directory because it sits in the build; this DLL lives in the mods folder, so the game executable
 * is what has to be matched instead.
 */
fs::path GetGameDirectory()
{
    wchar_t buffer[MAX_PATH];
    DWORD length = GetModuleFileNameW(nullptr, buffer, MAX_PATH);
    if (length == 0 || length == MAX_PATH) return {};
    return fs::path(buffer).parent_path();
}

/*
 * The launcher writes the manifest into the profile's data folder, which is junctioned from its
 * channel's roaming path, so both roots are searched exactly as the proxy searches them.
 */
std::vector<fs::path> GetSessionFolders()
{
    std::vector<fs::path> folders;

    char appdata[MAX_PATH];
    if (GetEnvironmentVariableA("APPDATA", appdata, MAX_PATH) != 0) {
        folders.push_back(fs::path(appdata) / "Minecraft Bedrock");
        folders.push_back(fs::path(appdata) / "Minecraft Bedrock Preview");
    }

    return folders;
}

/// The other channel's manifest is read during discovery, so a bad one there must not be fatal.
std::optional<json> TryReadJson(const fs::path& path)
{
    std::ifstream file(path);
    if (!file.is_open()) return std::nullopt;

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    try {
        return json::parse(buffer.str());
    }
    catch (const std::exception& e) {
        Log::Warning("Could not parse '{}': {}", path.generic_string(), e.what());
        return std::nullopt;
    }
}

SessionMod ReadMod(const json& entry, const std::string& field)
{
    Assert(entry.is_object(), "Session field '{}' should contain objects", field);
    Assert(entry.contains("id") && entry["id"].is_string(), "Session field '{}.id' should be a string", field);
    Assert(entry.contains("path") && entry["path"].is_string(), "Session field '{}.path' should be a string", field);

    return SessionMod{
        entry["id"].get<std::string>(),
        fs::path(entry["path"].get<std::string>())
    };
}
} // namespace

SessionManifest SessionManifest::FromFile(const fs::path& manifestPath)
{
    std::optional<json> parsed = TryReadJson(manifestPath);
    Assert(parsed.has_value(), "Failed to read session manifest at '{}'", manifestPath.generic_string());

    json& data = *parsed;
    const int schema = data.value("schema", 0);
    Assert(schema == SESSION_SCHEMA, "Session schema {} is unsupported (this runtime speaks {}). Update the launcher or the runtime", schema, SESSION_SCHEMA);

    Assert(data["profile"].is_object(), "Required field 'profile' should be an object in the session manifest");
    Assert(data["version"].is_object(), "Required field 'version' should be an object in the session manifest");
    Assert(data["mods"].is_array(), "Required field 'mods' should be an array in the session manifest");
    Assert(data["developerMode"].is_boolean(), "Required field 'developerMode' should be a boolean in the session manifest");

    SessionManifest manifest;
    manifest.profileUuid = data["profile"].value("uuid", "");
    manifest.profileName = data["profile"].value("name", "");
    manifest.channel = data.value("channel", "");
    manifest.developerMode = data["developerMode"].get<bool>();

    manifest.versionUuid = data["version"].value("uuid", "");
    manifest.versionLabel = data["version"].value("label", "");
    manifest.versionDirectory = fs::path(data["version"].value("path", ""));

    // A vanilla profile carries no runtime, in which case nothing injected this DLL.
    if (data.contains("runtime") && !data["runtime"].is_null())
        manifest.runtime = ReadMod(data["runtime"], "runtime");

    for (const auto& entry : data["mods"]) {
        manifest.mods.push_back(ReadMod(entry, "mods"));
    }

    manifest.dataDirectory = manifestPath.parent_path();
    return manifest;
}

SessionManifest SessionManifest::FindForCurrentProcess()
{
    const fs::path gameDirectory = GetGameDirectory();
    Assert(!gameDirectory.empty(), "Could not resolve the game's own directory");

    for (const fs::path& folder : GetSessionFolders()) {
        const fs::path manifestPath = folder / SESSION_FILENAME;

        std::optional<json> data = TryReadJson(manifestPath);
        if (!data.has_value()) continue;

        // Both channels leave a readable manifest behind, so the version path is what proves ownership
        const json& version = (*data)["version"];
        if (!version.is_object() || !version.contains("path") || !version["path"].is_string()) continue;
        if (!SamePath(fs::path(version["path"].get<std::string>()), gameDirectory)) continue;

        SessionManifest manifest = FromFile(manifestPath);
        Log::Info("Session: '{}' ({}) at {}", manifest.profileName, manifest.channel, manifestPath.generic_string());
        return manifest;
    }

    AssertFail("No session manifest describes '{}'. Launch through the Amethyst Launcher", gameDirectory.generic_string());
}
} // namespace Amethyst
