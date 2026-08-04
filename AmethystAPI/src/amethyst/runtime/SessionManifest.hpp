#pragma once
#include <filesystem>
#include <optional>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace Amethyst {
// Launcher -> runtime contract version, see Amethyst-Launcher/src/renderer/src/scripts/session/Session.ts
constexpr int SESSION_SCHEMA = 1;

constexpr const char* SESSION_FILENAME = ".amethyst-session.json";

struct SessionMod {
    // Folder name of the mod, e.g. "Amethyst-Runtime@0.0.0-dev"
    std::string id;
    fs::path directory;
};

/// What the launcher decided this launch should be, written next to the game's data before activation.
class SessionManifest {
public:
    std::string profileUuid;
    std::string profileName;
    std::string channel;

    std::string versionUuid;
    std::string versionLabel;
    fs::path versionDirectory;

    std::optional<SessionMod> runtime;
    std::vector<SessionMod> mods;

    bool developerMode = false;

    // The profile's game data folder, which is where the manifest itself lives
    fs::path dataDirectory;

    SessionManifest() = default;

    static SessionManifest FromFile(const fs::path& manifestPath);

    /// Finds the manifest describing this process, asserting if no launcher session claims it.
    static SessionManifest FindForCurrentProcess();
};
} // namespace Amethyst
