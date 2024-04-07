#include "minecraft/src-client/common/client/renderer/block/BlockTessellator.hpp"

//mce::Mesh* BlockTessellator::getMeshForBlock(Tessellator* tessellator, const Block* block) {
//    using function = mce::Mesh*(BlockTessellator::*)(Tessellator*, const Block*);
//    static auto func = std::bit_cast<function>(SigScan("48 89 5C 24 ? 55 56 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4D 8B D8"));
//    return (this->*func)(tessellator, block);
//}

void BlockTessellator::appendTessellatedBlock(Tessellator *tessellator, const Block *block) {
    using function = decltype(&BlockTessellator::appendTessellatedBlock);
    static auto func = std::bit_cast<function>(SigScan("48 8B C4 48 89 58 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 44 0F 29 40 ? 44 0F 29 48 ? 44 0F 29 90 ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4D 8B F8"));
    (this->*func)(tessellator, block);
}

int64_t BlockTessellator::tessellateInWorld(Tessellator &tessellator, const Block &block, const BlockPos &pos, bool a5, bool a6) {
    using function = decltype(&BlockTessellator::tessellateInWorld);
    static auto func = std::bit_cast<function>(SigScan("40 53 55 56 57 41 56 48 83 EC ? 80 79"));
    return (this->*func)(tessellator, block, pos, a5, a6);
}
