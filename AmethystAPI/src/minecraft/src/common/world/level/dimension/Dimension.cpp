#include "minecraft/src/common/world/level/dimension/Dimension.hpp"
#include <minecraft/src/common/world/level/dimension/DimensionHeightRange.hpp>
#include <amethyst/Memory.hpp>

BlockSource& Dimension::getBlockSourceFromMainChunkSource() const
{
    return *mBlockSource;
}