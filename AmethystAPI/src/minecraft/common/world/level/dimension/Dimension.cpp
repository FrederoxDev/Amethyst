#include "minecraft/common/world/level/dimension/Dimension.h"

const BlockSource* Dimension::getBlockSourceFromMainChunkSource() {
    return reinterpret_cast<const BlockSource*>(this + 204);
}