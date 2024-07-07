#pragma once
#include <cstdint>

class BlockSource;
class BlockActor;
class Actor;
class Block;
class BlockPos;
struct ActorBlockSyncMessage;
class BlockPos;

enum class BlockChangedEventTarget : unsigned char {
    SelfBlock,
    NeighborBlock
};

class BlockSourceListener {
public:
    virtual ~BlockSourceListener() = default;

    virtual void onSourceCreated(BlockSource& source) {};

    virtual void onSourceDestroyed(BlockSource& source) {};

    virtual void onAreaChanged(BlockSource& source, const BlockPos& min, const BlockPos& max) {};

    virtual void onBlockChanged(BlockSource& source, const BlockPos& pos, uint32_t layer, const Block& block, const Block& oldBlock, int updateFlags, const ActorBlockSyncMessage* syncMsg, BlockChangedEventTarget eventTarget, Actor* blockChangeSource) {};

    virtual void onBrightnessChanged(BlockSource& source, const BlockPos& pos)
    {
        this->onAreaChanged(source, pos, pos);
    }

    virtual void onBlockEntityChanged(BlockSource& source, BlockActor& blockEntity) {};

    virtual void onEntityChanged(BlockSource& source, Actor& entity) {};

    virtual void onBlockEvent(BlockSource& source, int x, int y, int z, int b0, int b1) {};
};
