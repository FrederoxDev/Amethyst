#include "minecraft/src/common/world/level/dimension/Dimension.hpp"

BlockSource* Dimension::getBlockSourceFromMainChunkSource()
{
    auto source = reinterpret_cast<BlockSource*>(this + 204);
    return source;
}