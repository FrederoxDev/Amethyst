#include "minecraft/src/common/world/level/dimension/Dimension.h"

BlockSource* Dimension::getBlockSourceFromMainChunkSource() {
    BlockSource* source = reinterpret_cast<BlockSource*>(this + 204);
    return source;
}