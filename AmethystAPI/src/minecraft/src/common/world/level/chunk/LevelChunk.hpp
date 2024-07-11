#pragma once
#include <minecraft/src-deps/core/threading/Mutex.hpp>
#include <minecraft/src/common/world/level/ChunkBlockPos.hpp>
#include <minecraft/src/common/world/level/ChunkPos.hpp>
#include <minecraft/src/common/world/level/chunk/BlockVolume.hpp>
#include <minecraft/src/common/world/level/chunk/ChunkState.hpp>
#include <minecraft/src/common/world/level/chunk/LevelChunkFormat.hpp>
#include <unordered_map>

class Block;
class BlockPos;
class BlockActor;
class BlockSource;
class Level;
class Dimension;
class ChunkSource;
class ActorLink;

class LevelChunk {
public:
    /* this + 0    */ Bedrock::Threading::Mutex mBlockEntityAccessLock;
    /* this + 80   */ Level* mLevel;
    /* this + 88   */ Dimension* mDimension;
    /* this + 96  */ BlockPos mMin;
    /* this + 108  */ BlockPos mMax;
    /* this + 120  */ ChunkPos mPosition;
    std::byte padding8[8];
    /* this + 136  */ ChunkSource* mGenerator;
    /* this + 144  */ std::optional<LevelChunkFormat> mLoadedFormat;
    /* this + 152  */ std::string mSerializedEntitiesBuffer;
    /* this + 184  */ bool mHadSerializedEntities;
    /* this + 192  */ std::vector<ActorLink> mUnresolvedActorLinks;
    /* this + 216  */ std::atomic<ChunkState> mLoadState;
    /* this + 217  */ std::byte padding225[4184 - 217];
    /* this + 4184 */ std::unordered_map<ChunkBlockPos, std::shared_ptr<BlockActor>> mBlockEntities;

public:
    BlockActor* getBlockEntity(const ChunkBlockPos& chunkPos);

    // 1.21.0.3 - 40 ? 57 41 ? 48 83 ? ? 4C 8B ? 41 8B ? 48 8B ? 48 8B
    void setBlockVolume(BlockVolume* blockVolume, unsigned int param2);

    // 1.20.71.1 - 40 55 53 56 57 41 54 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 49 8B F1 4D 8B F8 48 8B DA
    // Found by caller of BlockLegacy::newBlockEntity
    std::shared_ptr<BlockActor> _createBlockEntity(const BlockPos& pos, BlockSource* currentSource, const Block& current, const Block& old);

    // Custom helper functions
    std::shared_ptr<BlockActor> getAndRemoveBlockActor(const ChunkBlockPos& pos);
    void setBlockActor(const ChunkBlockPos& pos, std::shared_ptr<BlockActor> actorShared);
};