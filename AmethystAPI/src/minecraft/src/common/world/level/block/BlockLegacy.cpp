#include "minecraft/src/common/world/level/block/BlockLegacy.hpp"


BlockLegacy::~BlockLegacy() {

}

// 1.20.71.1 - Re-Implemented
short BlockLegacy::getBlockItemId()
{
    if (mID <= 0xFF) return mID;
    return 255 - mID;
}

void BlockLegacy::setDestroyTime(float destroyTime, float explosionResistance)
{
    mDestroySpeed = destroyTime;
    mExplosionResistance = explosionResistance;
}
