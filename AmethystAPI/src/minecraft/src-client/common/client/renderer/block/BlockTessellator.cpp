#include "minecraft/src-client/common/client/renderer/block/BlockTessellator.h"

mce::Mesh* BlockTessellator::getMeshForBlock(Tessellator* tessellator, const Block* block) {
    using function = mce::Mesh*(__thiscall*)(BlockTessellator*, Tessellator*, const Block*);
    static auto func = reinterpret_cast<function>(SigScan("48 89 5C 24 ? 55 56 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4D 8B D8"));
    return func(this, tessellator, block);
}
