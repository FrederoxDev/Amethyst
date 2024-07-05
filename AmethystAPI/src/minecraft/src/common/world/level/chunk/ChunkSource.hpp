#pragma once

#include <minecraft/src-deps/core/utility/NonOwnerPointer.hpp>
#include <minecraft/src/common/world/level/dimension/Dimension.hpp>
#include <memory>
#include <atomic>
#include <unordered_map>


class ChunkSource : public Bedrock::EnableNonOwnerReferences {
public:
    enum class LoadMode : int {
        None = 0x0,
        Deferred = 0x1,
    };

    int mChunkSide;                             
    class Level* mLevel;                        
    class Dimension* mDimension;               
    class ChunkSource* mParent;                           
    std::unique_ptr<ChunkSource> mOwnedParent;     
    class LevelChunkBuilderData* mLevelChunkBuilderData; 
    std::atomic_bool mShuttingDown;               
    char filler[32];                           


public:
    virtual ~ChunkSource();
    virtual void shutdown();
    virtual bool isShutdownDone();
    virtual std::shared_ptr<class LevelChunk> getExistingChunk(class ChunkPos const&);
    virtual std::shared_ptr<class LevelChunk> getRandomChunk(class Random& random);
    virtual bool isChunkKnown(class ChunkPos const& chunkPos);
    virtual bool isChunkSaved(class ChunkPos const& chunkPos);
    virtual std::shared_ptr<class LevelChunk> createNewChunk(class ChunkPos const& cp, ::ChunkSource::LoadMode lm, bool readOnly);
    virtual std::shared_ptr<class LevelChunk> getOrLoadChunk(class ChunkPos const& cp, ::ChunkSource::LoadMode lm, bool readOnly);
    virtual bool postProcess(class ChunkViewSource& neighborhood);
    virtual void checkAndReplaceChunk(class ChunkViewSource& neighborhood, class LevelChunk& lc);
    virtual void loadChunk(class LevelChunk& lc, bool forceImmediateReplacementDataLoad);
    virtual void postProcessMobsAt(class BlockSource& region, int chunkWestBlock, int chunkNorthBlock, class Random& random);
    virtual bool saveLiveChunk(class LevelChunk& lc);
    virtual void writeEntityChunkTransfer(class LevelChunk& levelChunk);
    virtual void writeEntityChunkTransfersToUnloadedChunk(class ChunkKey const&, std::vector<struct ActorUnloadedChunkTransferEntry> const&);
    virtual void deserializeActorStorageToLevelChunk(class LevelChunk&);
    virtual void hintDiscardBatchBegin();
    virtual void hintDiscardBatchEnd();
    virtual void acquireDiscarded(std::unique_ptr<class LevelChunk, struct LevelChunkFinalDeleter> ptr);
    virtual void compact();
    virtual void flushPendingDiscardedChunkWrites();
    virtual void flushThreadBatch();
    virtual bool isWithinWorldLimit(class ChunkPos const& cp) const;
    virtual std::unordered_map<class ChunkPos, std::weak_ptr<class LevelChunk>> const* getChunkMap();
    virtual std::unordered_map<class ChunkPos, std::weak_ptr<class LevelChunk>> const& getStorage() const;
    virtual void clearDeletedEntities();
    virtual bool canCreateViews() const;
    virtual std::unique_ptr<class BlendingDataProvider> tryGetBlendingDataProvider();
    virtual std::shared_ptr<class LevelChunkMetaDataDictionary> loadLevelChunkMetaDataDictionary();
    virtual void setLevelChunk(std::shared_ptr<class LevelChunk>);
    virtual bool canLaunchTasks() const;
    virtual bool chunkPosNeedsBlending(class ChunkPos const& cp);

public:
    ChunkSource(Dimension* dimension, int side);

};

// Ripped from levilamina headers. I verified its all correct. Just meant i didnt have to hand write all the virtuals lol.

static_assert(sizeof(ChunkSource) == 0x70, "ChunkSource size is incorrect");