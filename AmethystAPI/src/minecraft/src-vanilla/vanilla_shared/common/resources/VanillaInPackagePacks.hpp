#pragma once
#include "minecraft/src/common/resources/InPackagePacks.hpp"

class VanillaInPackagePacks : public IInPackagePacks {
public:
    // 1.20.71.1 - 48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 55 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 8B FA 48 89 55 ? 33 F6
    virtual std::vector<IInPackagePacks::MetaData> getPacks(PackType packType) const override;
};