#include "amethyst/runtime/mod/ModGraph.hpp"
#include <functional>

namespace Amethyst {
void ModGraph::Clear() {
	mMods.clear();
	mErrors.clear();
}

void ModGraph::SortAndValidate(const ModRepository& repository, const std::unordered_set<std::string>& profileMods) {
    Clear();
    const ModInfoMap& repoMods = repository.GetMods();

    std::unordered_set<const ModInfo*> visited;
    std::unordered_set<const ModInfo*> visiting;
    std::vector<const ModInfo*> stack;

    // Helper to push a ModError
    auto pushError = [&](
        const ModInfo& info, 
        ModErrorType type, 
        const std::string& message,
        std::unordered_map<std::string, std::string> data) 
    {
        mErrors.push_back(ModError{
            ModErrorStep::Resolving,
            type,
            info.UUID,
            message,
            std::move(data)
        });
    };

    std::function<bool(const std::shared_ptr<const ModInfo>&)> visit = [&](const std::shared_ptr<const ModInfo>& info) -> bool {
        if (visited.contains(info.get())) return true;
        if (visiting.contains(info.get())) {
            // Detected a cycle
            std::string cycle;
            for (const auto* modInStack : stack) {
                cycle += modInStack->GetVersionedName() + " -> ";
            }
            cycle += info->GetVersionedName();

            pushError(
                *info, 
                ModErrorType::CircularDependency,
                "Cyclic dependency detected: {cycle}",
                {
                    { "{cycle}", cycle }
                }
            );

            return false;
        }

        visiting.insert(info.get());
        StackGuard<const ModInfo*> guard(stack, info.get()); // RAII push/pop
        bool success = true;

        // Visit dependencies
        for (const auto& dep : info->Dependencies) {
            const ModInfo* found = nullptr;

            // Find matching mod in repo
            for (const auto& [uuid, mod] : repoMods) {
                if (!profileMods.contains(mod->GetVersionedName()))
                    continue; // Don't force-load non-launcher mods
                if (mod->Namespace == dep.Namespace && dep.MatchesMod(*mod, false)) {
                    found = mod.get();
                    // Check version
                    if (!dep.MatchesVersion(mod->Version)) {
                        if (!dep.IsSoft) {
                            pushError(
                                *info,
                                ModErrorType::WrongDependencyVersion,
                                "Mod '{mod}' requires '{dep}' version '{ver}', but found version '{found_ver}'",
                                {
                                    { "{mod}", info->GetVersionedName() },
                                    { "{dep}", std::format("{} (aka {})", dep.Namespace, mod->Name) },
                                    { "{ver}", dep.RangeString },
                                    { "{found_ver}", mod->Version.to_string() }
                                }
                            );
                            success = false;
                        }
                        break;
                    }

                    // Recurse into the dependency
                    if (!visit(mod)) 
                        success = false;
                    break; // Found the dependency
                }
            }

            // If no matching mod found and dependency is required
            if (!found && !dep.IsSoft) {
                pushError(
                    *info, 
                    ModErrorType::MissingDependency,
                    "Mod '{mod}' requires '{dep}', but it was not found",
                    {
                        { "{mod}", info->GetVersionedName() },
                        { "{dep}", dep.GetDependencyIdentification() }
                    }
                );
                success = false;
            }
        }

        visiting.erase(info.get());
        visited.insert(info.get());
        if (success) {
            mMods.emplace_back(info);
        }
        return success;
    };

    std::unordered_set<std::string> allLoadedMods = std::unordered_set<std::string>();

    // Visit all launcher mods
    for (const auto& [uuid, mod] : repoMods) {
        std::string versionedName = mod->GetVersionedName();

        if (!profileMods.contains(versionedName))
            continue;

        visit(mod);
        allLoadedMods.insert(versionedName);
    }

    // Verify all mods in the profile were loaded
    for (const auto& mod : profileMods) {
        if (allLoadedMods.contains(mod)) continue;
        AssertFail("Failed to load mod '{}' named by the launcher session", mod);
    }
}

const std::vector<std::shared_ptr<const ModInfo>>& ModGraph::GetMods() const {
    return mMods;
}

const std::vector<ModError>& ModGraph::GetErrors() const {
    return mErrors;
}

bool ModGraph::HasErrors() const {
    return !mErrors.empty();
}

size_t ModGraph::GetModCount() const {
    return mMods.size();
}
} // namespace Amethyst