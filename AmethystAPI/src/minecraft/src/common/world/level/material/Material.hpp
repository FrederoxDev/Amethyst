#pragma once
#include "minecraft/src/common/world/level/material/MaterialType.hpp"

class Material {
public:
    MaterialType mType;
    bool mNeverBuildable;
    bool mAlwaysDestroyable;
    bool mReplaceable;
    bool mLiquid;
    float mTranslucency;
    bool mBlocksMotion;
    bool mBlocksPrecipitation;
    bool mSolid;
    bool mSuperHot;
};