#include "amethyst/runtime/mod/ModRepository.hpp"
#include "amethyst/Log.hpp"
#include "amethyst/Memory.hpp"

namespace Amethyst {
namespace {
std::string JoinGameBuilds(const std::vector<GameBuild>& gameBuilds)
{
    std::string joined;
    for (const GameBuild& gameBuild : gameBuilds) {
        if (!joined.empty()) joined += ", ";
        joined += std::format("{} ({})", gameBuild.Version, gameBuild.Guid);
    }
    return joined;
}

std::optional<ModError> CheckGameBuild(const ModInfo& modInfo)
{
    if (modInfo.GameBuilds.empty()) return std::nullopt;

    std::optional<MinecraftBuildId> buildId = GetMinecraftBuildId();
    if (!buildId.has_value()) {
        return ModError{
            ModErrorStep::Collecting,
            ModErrorType::IncompatibleGameBuild,
            modInfo.UUID,
            "'{mod}' only runs on specific Minecraft builds, but this game's build could not be identified, so it was not loaded. The builds it accepts are: {modBuilds}",
            {
                { "{mod}", modInfo.GetVersionedName() },
                { "{modBuilds}", JoinGameBuilds(modInfo.GameBuilds) }
            }
        };
    }

    if (modInfo.SupportsGameBuild(buildId->Guid)) return std::nullopt;

    return ModError{
        ModErrorStep::Collecting,
        ModErrorType::IncompatibleGameBuild,
        modInfo.UUID,
        "'{mod}' was not loaded because it does not support this Minecraft build. This game is build {gameBuild}, and the mod accepts: {modBuilds}. Install a Minecraft version the mod supports, or get a build of the mod made for this one.",
        {
            { "{mod}", modInfo.GetVersionedName() },
            { "{gameBuild}", buildId->Guid },
            { "{modBuilds}", JoinGameBuilds(modInfo.GameBuilds) }
        }
    };
}
} // namespace

void ModRepository::LoadFromDirectories(const std::vector<fs::path>& directories)
{
    Clear();
    for (const fs::path& directory : directories) {
        auto result = ModInfo::FromFile(directory / "mod.json");
        if (!result) {
            mErrors.push_back(result.error());
            continue;
        }
        auto buildError = CheckGameBuild(*result);
        if (buildError.has_value()) {
            mErrors.push_back(*buildError);
            continue;
        }
        auto modInfo = std::make_shared<const ModInfo>(std::move(*result));
        if (mMods.contains(modInfo->UUID)) {
            Log::Warning("Mod with UUID '{}' already exists in repository, skipping duplicate from '{}'", modInfo->UUID, directory.generic_string());
            continue;
        }
        mMods.emplace(modInfo->UUID, modInfo);
    }
}

void ModRepository::Clear() {
    mMods.clear();
    mErrors.clear();
}

const ModInfoMap& ModRepository::GetMods() const {
    return mMods;
}

const std::vector<ModError>& ModRepository::GetErrors() const {
    return mErrors;
}

std::shared_ptr<const ModInfo> ModRepository::GetModByUUID(const std::string& uuid) const
{
    auto it = mMods.find(uuid);
    if (it != mMods.end()) {
        return it->second;
    }
    return nullptr;
}

std::shared_ptr<const ModInfo> ModRepository::GetModByNamespace(const std::string& modNamespace) const
{
    for (const auto& [uuid, mod] : mMods) {
        if (mod->Namespace == modNamespace) {
            return mod;
        }
    }
    return nullptr;
}

void Amethyst::ModRepository::AddMod(const ModInfoMap::const_iterator& pos, const std::shared_ptr<const ModInfo>& modInfo)
{
    mMods.insert(pos, { modInfo->UUID, modInfo });
}

bool ModRepository::HasModUUID(const std::string& uuid) const {
    return mMods.contains(uuid);
}

bool ModRepository::HasModNamespace(const std::string& modNamespace) const {
    for (const auto& [uuid, mod] : mMods) {
        if (mod->Namespace == modNamespace) {
            return true;
        }
    }
    return false;
}

bool ModRepository::HasErrors() const
{
    return !mErrors.empty();
}

size_t ModRepository::GetModCount() const {
    return mMods.size();
}
} // namespace Amethyst