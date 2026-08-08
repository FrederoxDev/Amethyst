
#include "Json.hpp"
#include "amethyst/Log.hpp"
#include <algorithm>
#include <cctype>
#include <fstream>
#include "ModInfo.hpp"
#include "amethyst/runtime/ModContext.hpp"

namespace Amethyst {
ModInfo::ModInfo(
    const std::string& uuid,
    const std::string& modNamespace,
    const std::string& name,
    const std::string& loggingName,
    const std::string& friendlyName,
    const Amethyst::Version& version,
    const std::vector<std::string>& authors,
    const std::vector<ModDependency>& dependencies,
    const std::vector<GameBuild>& gameBuilds,
    bool isRuntime,
    const fs::path& directory,
    const std::string& libraryName) :
    UUID(uuid),
    Namespace(modNamespace),
    Name(name),
    LoggingName(loggingName),
    FriendlyName(friendlyName),
    Version(version),
    Authors(authors),
    Dependencies(dependencies),
    GameBuilds(gameBuilds),
    IsRuntime(isRuntime),
    Directory(directory),
    LibraryName(libraryName)
{
}

std::string ModInfo::GetVersionedName() const
{
    // The folder name is what the launcher identifies a mod by, and it can differ from mod.json's version
    if (!Directory.empty())
        return Directory.filename().string();
    return std::format("{}@{}", Name, Version.to_string());
}

bool ModInfo::Equals(const ModInfo& other, bool compareVersions) const
{
    return UUID == other.UUID && Namespace == other.Namespace && (!compareVersions || Version == other.Version);
}

bool ModInfo::operator==(const ModInfo& other) const
{
    return Equals(other);
}

bool ModInfo::operator!=(const ModInfo& other) const
{
    return !(*this == other);
}

bool ModInfo::operator<(const ModInfo& other) const 
{
    return std::tie(Namespace, UUID) < std::tie(other.Namespace, other.UUID);
}

inline bool ModInfo::IsSameMod(const ModInfo& other) const
{
    return Equals(other, false);
}

std::string ModInfo::NormalizeGameBuild(const std::string& guid)
{
    std::string normalized;
    normalized.reserve(guid.size());

    for (unsigned char c : guid) {
        // People paste GUIDs in registry form, so braces and padding are not part of the identity
        if (c == '{' || c == '}' || std::isspace(c)) continue;
        normalized.push_back(static_cast<char>(std::toupper(c)));
    }

    return normalized;
}

bool ModInfo::SupportsGameBuild(const std::string& guid) const
{
    if (GameBuilds.empty()) return true;

    std::string normalized = NormalizeGameBuild(guid);
    return std::any_of(GameBuilds.begin(), GameBuilds.end(), [&](const GameBuild& gameBuild) {
        return gameBuild.Guid == normalized;
    });
}

std::expected<ModInfo, ModError> ModInfo::FromFile(const fs::path& jsonFile)
{
    std::ifstream modConfigFile(jsonFile);
    std::optional<std::string> uuid;

    if (!modConfigFile.is_open()) {
		Log::Info("Failed to open mod.json at {}", jsonFile.generic_string());

        return std::unexpected(ModError{
            ModErrorStep::Collecting,
            ModErrorType::IOError,
            uuid,
            "Failed to open mod.json, at '{path}'",
            {
                { "{path}", jsonFile.generic_string() }
            }
        });
    }

    std::stringstream buffer;
    buffer << modConfigFile.rdbuf();
    modConfigFile.close();
    std::string fileContents = buffer.str();

    nlohmann::json j = nlohmann::json::parse(fileContents);
    if (!j["meta"].is_object()) {
        return std::unexpected(ModError{
            ModErrorStep::Collecting,
            ModErrorType::ParseError,
            uuid,
            "Invalid mod info JSON: 'meta' is not an object",
            {
                { "{path}", jsonFile.generic_string() }
            }
        });
    }

    nlohmann::json meta = j["meta"];

    if (!meta["uuid"].is_string()) {
        return std::unexpected(ModError{
            ModErrorStep::Collecting,
            ModErrorType::ParseError,
            uuid,
            "Invalid mod info JSON: 'meta.uuid' is not a string",
            {
                { "{path}", jsonFile.generic_string() }
            }
        });
    }
    uuid = meta["uuid"].get<std::string>();

    if (!meta["namespace"].is_string()) {
        return std::unexpected(ModError{
            ModErrorStep::Collecting,
            ModErrorType::ParseError,
            uuid,
            "Invalid mod info JSON: 'meta.namespace' is not a string",
            { 
                { "{path}", jsonFile.generic_string() }
            }
        });
    }

    if (!meta["name"].is_string()) {
        return std::unexpected(ModError{
            ModErrorStep::Collecting,
            ModErrorType::ParseError,
            uuid,
            "Invalid mod info JSON: 'meta.name' is not a string",
            {
                { "{path}", jsonFile.generic_string() }
            }
        });
    }

    if (!meta["version"].is_string()) {
        return std::unexpected(ModError{
            ModErrorStep::Collecting,
            ModErrorType::ParseError,
            uuid,
            "Invalid mod info JSON: 'meta.version' is not a string",
            {
                { "{path}", jsonFile.generic_string() }
            }
        });
    }

    Amethyst::Version version;
    if (!semver::parse(meta["version"].get<std::string>(), version)) {
        return std::unexpected(ModError{
            ModErrorStep::Collecting,
            ModErrorType::ParseError,
            uuid,
            "Invalid mod info JSON: 'meta.version' is not a valid semantic version",
            {
                { "{path}", jsonFile.generic_string() }
            }
        });
    }

    std::string modNamespace = meta["namespace"].get<std::string>();
    std::string name = meta["name"].get<std::string>();
    std::string loggingName = name;
    std::string friendlyName = name;
    std::vector<std::string> authors;
    std::vector<ModDependency> dependencies;
    bool isRuntime = meta.value("is_runtime", false);

    if (meta.contains("log_name") && meta["log_name"].is_string()) {
        loggingName = meta["log_name"].get<std::string>();
    }

    if (meta.contains("friendly_name") && meta["friendly_name"].is_string()) {
        friendlyName = meta["friendly_name"].get<std::string>();
    }

    if (meta.contains("author")) {
        if (meta["author"].is_string()) {
            authors.push_back(meta["author"].get<std::string>());
        }
        else if (meta["author"].is_array()) {
            for (const auto& author : meta["author"]) {
                if (author.is_string()) {
                    authors.push_back(author.get<std::string>());
                }
            }
        }
    }

    if (meta.contains("dependencies") && meta["dependencies"].is_array()) {
        for (const auto& dependencyObj : meta["dependencies"]) {
            if (dependencyObj.is_object()) {
                dependencies.push_back(ModDependency(
                    dependencyObj.value("dependency_uuid", ""),
                    dependencyObj.value("dependency_namespace", ""),
                    dependencyObj.value("version_range", ""),
                    dependencyObj.value("is_soft", false)
                ));
            }
        }
    }

    auto& platform = Amethyst::GetPlatform();
    std::vector<GameBuild> gameBuilds;

    if (meta.contains("platforms") && meta["platforms"].is_object()) {
        const nlohmann::json& platforms = meta["platforms"];
        auto entry = platforms.find(platform.GetPlatformFolderName());

        if (entry != platforms.end() && entry->is_object() && entry->contains("game_builds") && (*entry)["game_builds"].is_array()) {
            for (const auto& gameBuild : (*entry)["game_builds"]) {
                // A malformed entry must not silently drop the guard, or the mod loads against a build it was never made for
                if (!gameBuild.is_object() || !gameBuild.contains("version") || !gameBuild["version"].is_string()
                    || !gameBuild.contains("guid") || !gameBuild["guid"].is_string()) {
                    return std::unexpected(ModError{
                        ModErrorStep::Collecting,
                        ModErrorType::ParseError,
                        uuid,
                        "Invalid mod info JSON: every entry of 'game_builds' needs a 'version' and a 'guid' string",
                        {
                            { "{path}", jsonFile.generic_string() }
                        }
                    });
                }

                gameBuilds.push_back(GameBuild{
                    gameBuild["version"].get<std::string>(),
                    NormalizeGameBuild(gameBuild["guid"].get<std::string>())
                });
            }
        }
    }

    std::string versionedName = std::format("{}@{}", name, version.to_string());
    fs::path directory = jsonFile.parent_path();
    std::string libraryName = std::format("{}.dll", name);

    if (!fs::exists(directory / platform.GetPlatformFolderName() / libraryName)) {
        return std::unexpected(ModError{
            ModErrorStep::Collecting,
            ModErrorType::IOError,
            uuid,
            "Could not find library for '{mod}'!",
            {
                { "{path}", (directory / libraryName).generic_string() },
                { "{mod}", versionedName }
            }
        });
    }

    return ModInfo(uuid.value(), modNamespace, name, loggingName, friendlyName, version, authors, dependencies, gameBuilds, isRuntime, directory, libraryName);
}
} // namespace Amethyst