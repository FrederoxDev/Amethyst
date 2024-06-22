#include "ChestBlock.hpp"

// 1.21.0.3 - Re-Implemented
bool ChestBlock::canProvideSupport(const Block& block, unsigned char face, BlockSupportType type) const
{
    return face == 0 && (type & 0xFFFFFFFD) == 0;
}

// 1.21.0.3 - Re-Implemented
bool ChestBlock::isContainerBlock() const
{
    return true;
}

// 1.21.0.3 - Re-Implemented
bool ChestBlock::isSignalSource() const
{
    return mChestType == ChestType::Trapped;
}

// 1.21.0.3 - Re-Implemented
bool ChestBlock::shouldConnectToRedstone(BlockSource& block_source, const BlockPos& block_pos, Direction::Type param) const
{
    return mChestType == ChestType::Trapped;
}

// 1.21.0.3 - Re-Implemented
bool ChestBlock::detachesOnPistonMove(BlockSource& block_source, BlockPos const& block_pos) const
{
    return true;
}

// 1.21.0.3 - Re-Implemented
bool ChestBlock::breaksFallingBlocks(const Block& block, BaseGameVersion version) const
{
    return true;
}

// 1.21.0.3 - Re-Implemented
bool ChestBlock::hasComparatorSignal() const
{
    return true;
}

// 1.21.0.3 - Re-Implemented
bool ChestBlock::isInteractive() const
{
    return true;
}


