#include "minecraft/src/common/world/level/dimension/Dimension.hpp"
#include <amethyst/Memory.hpp>

BlockSource& Dimension::getBlockSourceFromMainChunkSource() const
{
    return *mBlockSource;
}