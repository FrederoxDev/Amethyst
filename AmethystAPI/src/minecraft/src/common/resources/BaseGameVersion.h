#pragma once
#include "minecraft/src-deps/core/semVer/SemVersion.h"

class BaseGameVersion {
public:
    SemVersion mSemVersion;
    bool mNeverCompatible;
};