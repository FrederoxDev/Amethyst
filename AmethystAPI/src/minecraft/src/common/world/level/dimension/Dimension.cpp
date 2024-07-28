#include "minecraft/src/common/world/level/dimension/Dimension.hpp"
#include <minecraft/src/common/world/level/dimension/DimensionHeightRange.hpp>
#include <amethyst/Memory.hpp>

BlockSource& Dimension::getBlockSourceFromMainChunkSource() const
{
    return *mBlockSource;
}

const Level& Dimension::getLevelConst() const
{
    return *(Level*)mLevel;
}

Level& Dimension::getLevel() const
{
    return *(Level*)mLevel;
}
