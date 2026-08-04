#include "amethyst/runtime/mod/ModRepository.hpp"
#include "amethyst/Log.hpp"

namespace Amethyst {
void ModRepository::LoadFromDirectories(const std::vector<fs::path>& directories)
{
    Clear();
    for (const fs::path& directory : directories) {
        auto result = ModInfo::FromFile(directory / "mod.json");
        if (!result) {
            mErrors.push_back(result.error());
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