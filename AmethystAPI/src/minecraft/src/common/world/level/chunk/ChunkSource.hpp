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

/**@vtable*/
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
	/**
	* @symbol {??1ChunkSource@@UEAA@XZ}
	* @vIndex {0} 
	*/
	virtual ~ChunkSource();
    
	/**@vIndex {1} */
	virtual void shutdown();
    
	/**@vIndex {2} */
	virtual bool isShutdownDone();
    
	/**@vIndex {3} */
	virtual std::shared_ptr<LevelChunk> getExistingChunk(const ChunkPos&);
    
	/**@vIndex {4} */
	virtual std::shared_ptr<LevelChunk> getRandomChunk(Random& random);
    
	/**@vIndex {5} */
	virtual bool isChunkKnown(const ChunkPos& chunkPos);
    
	/**@vIndex {6} */
	virtual bool isChunkSaved(const ChunkPos& chunkPos);
    
	/**@vIndex {7} */
	virtual std::shared_ptr<LevelChunk> createNewChunk(const ChunkPos& cp, ChunkSource::LoadMode lm, bool readOnly);
    
	/**@vIndex {8} */
	virtual std::shared_ptr<LevelChunk> getOrLoadChunk(const ChunkPos& cp, ChunkSource::LoadMode lm, bool readOnly);
    
	/**@vIndex {9} */
	virtual bool postProcess(ChunkViewSource& neighborhood);
    
	/**@vIndex {10} */
	virtual void checkAndReplaceChunk(ChunkViewSource& neighborhood, LevelChunk& lc);
    
	/**@vIndex {11} */
	virtual void loadChunk(LevelChunk& lc, bool forceImmediateReplacementDataLoad);
    
	/**@vIndex {12} */
	virtual void postProcessMobsAt(class BlockSource& region, int chunkWestBlock, int chunkNorthBlock, Random& random);
    
	/**@vIndex {13} */
	virtual bool saveLiveChunk(LevelChunk& lc);
    
	/**@vIndex {14} */
	virtual void writeEntityChunkTransfer(LevelChunk& levelChunk);
    
	/**@vIndex {15} */
	virtual void writeEntityChunkTransfersToUnloadedChunk(const ChunkKey&, const std::vector<ActorUnloadedChunkTransferEntry>&);
    
	/**@vIndex {16} */
	virtual void deserializeActorStorageToLevelChunk(LevelChunk&);
    
	/**@vIndex {17} */
	virtual void hintDiscardBatchBegin();
    
	/**@vIndex {18} */
	virtual void hintDiscardBatchEnd();
    
	/**@vIndex {19} */
	virtual void acquireDiscarded(std::unique_ptr<LevelChunk, struct LevelChunkFinalDeleter> ptr);
    
	/**@vIndex {20} */
	virtual void compact();
    
	/**@vIndex {21} */
	virtual void flushPendingDiscardedChunkWrites();
    
	/**@vIndex {22} */
	virtual void flushThreadBatch();
    
	/**@vIndex {23} */
	virtual bool isWithinWorldLimit(const ChunkPos& cp) const;
    
	/**@vIndex {24} */
	virtual const std::unordered_map<ChunkPos, std::weak_ptr<LevelChunk>>* getChunkMap();
    
	/**@vIndex {25} */
	virtual const std::unordered_map<ChunkPos, std::weak_ptr<LevelChunk>>& getStorage() const;
    
	/**@vIndex {26} */
	virtual void clearDeletedEntities();
    
	/**@vIndex {27} */
	virtual bool canCreateViews() const;
    
	/**@vIndex {28} */
	virtual std::unique_ptr<BlendingDataProvider> tryGetBlendingDataProvider();
    
	/**@vIndex {29} */
	virtual std::shared_ptr<LevelChunkMetaDataDictionary> loadLevelChunkMetaDataDictionary();
    
	/**@vIndex {30} */
	virtual void setLevelChunk(std::shared_ptr<LevelChunk>);
    
	/**@vIndex {31} */
	virtual bool canLaunchTasks() const;
    
	/**@vIndex {32} */
	virtual bool chunkPosNeedsBlending(const ChunkPos& cp);

public:
    ChunkSource(Dimension* dimension, int side);
};

static_assert(sizeof(ChunkSource) == 0x70, "ChunkSource size is incorrect");