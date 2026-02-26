/// @symbols
#pragma once
#include "mc/src/common/resources/InPackagePacks.hpp"
#include <amethyst/Imports.hpp>

class VanillaInPackagePacks : public IInPackagePacks {
public:
    // 1.20.71.1, 1.21.0.3 - 48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 55 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 8B ? 48 89 55 ? 33 F6
    /// @vidx {inherit, this}
    MC virtual std::vector<IInPackagePacks::MetaData> getPacks(PackType packType) const override;
};