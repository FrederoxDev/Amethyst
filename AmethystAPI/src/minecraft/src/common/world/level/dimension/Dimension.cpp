#include "common/world/level/dimension/Dimension.h"

BlockSource* Dimension::getBlockSourceFromMainChunkSource()
{
    auto source = reinterpret_cast<BlockSource*>(this + 204);
    return source;
}