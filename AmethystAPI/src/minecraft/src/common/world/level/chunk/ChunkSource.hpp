#pragma once
#include <memory>
#include <atomic>
#include <unordered_map>

#include <minecraft/src-deps/core/utility/NonOwnerPointer.hpp>
#include <minecraft/src-deps/core/utility/pubsub/Subscription.hpp>

class Level;
class LevelChunk;
class LevelChunkBuilderData;
class LevelChunkMetaDataDictionary;
class ChunkPos;
class Dimension;
class Random;
class ChunkKey;
struct ActorUnloadedChunkTransferEntry;
class BlendingDataProvider;
class ChunkViewSource;

class ChunkSource : public Bedrock::EnableNonOwnerReferences {
public:
    enum class LoadMode : int {
        None = 0x0,
        Deferred = 0x1,
    };

public:
    int mChunkSide;                             
    Level* mLevel;                        
    Dimension* mDimension;               
    ChunkSource* mParent;                           
    std::unique_ptr<ChunkSource> mOwnedParent;     
    LevelChunkBuilderData* mLevelChunkBuilderData; 
    std::atomic<bool> mShuttingDown;               
    Bedrock::PubSub::Subscription mOnSaveSubscription;
    Bedrock::PubSub::Subscription mOnLevelStorageAppSuspendSubscription;                     

public:
    virtual ~ChunkSource();
    virtual void shutdown();
    virtual bool isShutdownDone();
    virtual std::shared_ptr<LevelChunk> getExistingChunk(const ChunkPos&);
    virtual std::shared_ptr<LevelChunk> getRandomChunk(Random& random);
    virtual bool isChunkKnown(const ChunkPos& chunkPos);
    virtual bool isChunkSaved(const ChunkPos& chunkPos);
    virtual std::shared_ptr<LevelChunk> createNewChunk(const ChunkPos& cp, ChunkSource::LoadMode lm, bool readOnly);
    virtual std::shared_ptr<LevelChunk> getOrLoadChunk(const ChunkPos& cp, ChunkSource::LoadMode lm, bool readOnly);
    virtual bool postProcess(ChunkViewSource& neighborhood);
    virtual void checkAndReplaceChunk(ChunkViewSource& neighborhood, LevelChunk& lc);
    virtual void loadChunk(LevelChunk& lc, bool forceImmediateReplacementDataLoad);
    virtual void postProcessMobsAt(class BlockSource& region, int chunkWestBlock, int chunkNorthBlock, Random& random);
    virtual bool saveLiveChunk(LevelChunk& lc);
    virtual void writeEntityChunkTransfer(LevelChunk& levelChunk);
    virtual void writeEntityChunkTransfersToUnloadedChunk(const ChunkKey&, const std::vector<ActorUnloadedChunkTransferEntry>&);
    virtual void deserializeActorStorageToLevelChunk(LevelChunk&);
    virtual void hintDiscardBatchBegin();
    virtual void hintDiscardBatchEnd();
    virtual void acquireDiscarded(std::unique_ptr<LevelChunk, struct LevelChunkFinalDeleter> ptr);
    virtual void compact();
    virtual void flushPendingDiscardedChunkWrites();
    virtual void flushThreadBatch();
    virtual bool isWithinWorldLimit(const ChunkPos& cp) const;
    virtual const std::unordered_map<ChunkPos, std::weak_ptr<LevelChunk>>* getChunkMap();
    virtual const std::unordered_map<ChunkPos, std::weak_ptr<LevelChunk>>& getStorage() const;
    virtual void clearDeletedEntities();
    virtual bool canCreateViews() const;
    virtual std::unique_ptr<BlendingDataProvider> tryGetBlendingDataProvider();
    virtual std::shared_ptr<LevelChunkMetaDataDictionary> loadLevelChunkMetaDataDictionary();
    virtual void setLevelChunk(std::shared_ptr<LevelChunk>);
    virtual bool canLaunchTasks() const;
    virtual bool chunkPosNeedsBlending(const ChunkPos& cp);

public:
    ChunkSource(Dimension* dimension, int side);
};

// Ripped from levilamina headers. I verified its all correct. Just meant i didnt have to hand write all the virtuals lol.

static_assert(sizeof(ChunkSource) == 0x70, "ChunkSource size is incorrect");