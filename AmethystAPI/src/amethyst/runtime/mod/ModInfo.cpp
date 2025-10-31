
#include "Json.hpp"
#include "amethyst/Log.hpp"
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
    IsRuntime(isRuntime),
    Directory(directory),
    LibraryName(libraryName)
{
}

std::string ModInfo::GetVersionedName() const
{
    std::string versionedName = std::format("{}@{}", Name, Version.to_string());
    auto& platform = Amethyst::GetPlatform();
    if (!fs::exists(platform.GetAmethystFolder() / "mods" / versionedName)) {
        return std::format("{}@0.0.0-dev", Name);
    }
    return versionedName;
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

    std::string versionedName = std::format("{}@{}", name, version.to_string());
    fs::path directory = jsonFile.parent_path();
    std::string libraryName = std::format("{}.dll", name);
	auto& platform = Amethyst::GetPlatform();

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

    return ModInfo(uuid.value(), modNamespace, name, loggingName, friendlyName, version, authors, dependencies, isRuntime, directory, libraryName);
}
} // namespace Amethyst