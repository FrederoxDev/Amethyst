#pragma once

#include "minecraft/src-client/common/client/renderer/Tessellator.h"
#include "minecraft/src/common/world/level/block/Block.h"

class BlockTessellator {
public:
    // 1.20.51.1 - 48 89 5C 24 ? 55 56 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4D 8B D8
    mce::Mesh* getMeshForBlock(Tessellator* tessellator, const Block* block);
};