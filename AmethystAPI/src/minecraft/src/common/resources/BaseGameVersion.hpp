#pragma once
#include "minecraft/src-deps/core/semVer/SemVersion.hpp"

class BaseGameVersion {
public:
    SemVersion mSemVersion;
    bool mNeverCompatible;
};