#include "minecraft/src/common/world/gamemode/GameMode.hpp"
#include "minecraft/src/common/world/level/BlockSource.hpp"
#include "minecraft/src/common/world/level/block/Block.hpp"
#include "minecraft/src/common/world/actor/player/Player.hpp"
#include "minecraft/src/common/world/item/Item.hpp"

// Complete implementation
// 1.21.0.3 - no address, inlined.
BlockPos GameMode::_calculatePlacePos(ItemStack& heldStack, const BlockPos& pos, FacingID& face) {
    const Item* item = heldStack.getItem();

    if (item) {
        BlockPos result = pos;
        item->calculatePlacePos(heldStack, mPlayer, face, result);
        return result;
    }

    BlockSource& blockSource = mPlayer.getDimensionBlockSource();
    const Block& block = blockSource.getBlock(pos);

    if (block.canBeBuiltOver(blockSource, pos)) {
        face = Facing::Name::UP;
        return pos;
    }
    
    return pos.neighbor(face);
}