#pragma once
#include <cstddef>
#include <cstdint>
#include <string>
#include "minecraft/src-deps/core/threading/Mutex.hpp"
#include "minecraft/src-deps/core/utility/NonOwnerPointer.hpp"
#include <minecraft/src/common/world/level/chunk/ChunkSource.hpp>
#include "minecraft/src/common/world/level/dimension/DimensionHeightRange.hpp"
#include "minecraft/src/common/world/level/dimension/IDimension.hpp"
#include "minecraft/src/common/world/level/LevelListener.hpp"
#include "minecraft/src/common/world/level/saveddata/SavedData.hpp"
#include "minecraft/src/common/gamerefs/OwnerPtr.hpp"
#include "minecraft/src/common/world/level/Level.hpp"
#include "minecraft/src/common/world/level/storage/StorageVersion.hpp"
#include "minecraft/src/common/world/level/ChunkPos.hpp"
#include "minecraft/src/common/world/level/chunk/LevelChunkGarbageCollector.hpp"
#include "minecraft/src/common/world/level/levelgen/v1/FeatureTerrainAdjustments.hpp"
#include "minecraft/src/common/world/level/levelgen/structure/StructureSetRegistry.hpp"
#include <set>

enum class LimboEntitiesVersion : char {
    v0,
    v1_8_0,
    v1_10_0,
    v1_12_0,
    v1_16_210
};

struct ActorChunkTransferEntry {
    ChunkPos mOldChunkPos;
    ChunkPos mNewChunkPos;
};

namespace br::worldgen { struct StructureSetRegistry; }
namespace mce { class Color; }
class BlockSource;
class ILevel;
class Scheduler;
class DimensionHeightRange;
class DimensionBrightnessRamp;
class LevelChunkMetaData;
class RuntimeLightingManager;
class BaseLightTextureImageBuilder;
class BlockEventDispatcher;
class TaskGroup;
class PostprocessingManager;
class SubChunkInterlocker;
class Weather;
class Seasons;
class CircuitSystem;
class GameEventDispatcher;
class WeakEntityRef;
class WireframeQueue;
class ChunkSource;
class WorldGenerator;
class TickingAreaList;
class VillageManager;
class NetworkIdentifierWithSubId;
class ChunkLoadActionList;
class DelayActionList;
class SubChunkPos;
class UpdateSubChunkBlocksChangedInfo;
class ChunkBuildOrderPolicyBase;

/**@vtable */
class Dimension : public IDimension, public LevelListener, public SavedData, public Bedrock::EnableNonOwnerReferences, public std::enable_shared_from_this<Dimension> {
public:
    struct PlayerReplicationStructures;

    // Thanks Levilamina for free Dimension struct xx
    /* this + 104  */ std::vector<ActorChunkTransferEntry> mActorChunkTransferQueue;
    /* this + 128  */ std::unordered_map<ChunkKey, std::vector<ActorUnloadedChunkTransferEntry>> mActorUnloadedChunkTransferQueue;
    /* this + 192  */ ILevel* mLevel;
    /* this + 200  */ DimensionHeightRange mHeightRange;
    /* this + 204  */ int16_t mSeaLevel;
    /* this + 208  */ OwnerPtr<BlockSource> mBlockSource;
    /* this + 224  */ float mMobsPerChunkSurface[7];
    /* this + 252  */ float mMobsPerChunkUnderground[7];
    /* this + 280  */ BrightnessPair mDefaultBrightness;
    /* this + 288  */ std::unique_ptr<BaseLightTextureImageBuilder> mLightTextureImageBuilder;
    /* this + 296  */ std::unique_ptr<DimensionBrightnessRamp> mDimensionBrightnessRamp;
    /* this + 304  */ std::shared_ptr<LevelChunkMetaData> mTargetMetaData;
    /* this + 320  */ std::unique_ptr<RuntimeLightingManager> mRuntimeLightingManager;
    /* this + 328  */ std::string mName;
    /* this + 360  */ DimensionType mId;
    /* this + 364  */ bool mUltraWarm;
    /* this + 365  */ bool mHasCeiling;
    /* this + 366  */ bool mHasWeather;
    /* this + 367  */ bool mHasSkylight;
    /* this + 367  */ Brightness mSkyDarken;
    /* this + 376  */ std::unique_ptr<BlockEventDispatcher> mDispatcher;
    /* this + 384  */ std::unique_ptr<TaskGroup> mTaskGroup;
    /* this + 392  */ std::unique_ptr<TaskGroup> mChunkGenTaskGroup;
    /* this + 400  */ std::unique_ptr<PostprocessingManager> mPostProcessingManager;
    /* this + 408  */ std::unique_ptr<SubChunkInterlocker> mSubChunkInterlocker;
    /* this + 416  */ std::unique_ptr<ChunkSource> mChunkSource;
    /* this + 424  */ WorldGenerator* mWorldGenerator;
    /* this + 432  */ std::unique_ptr<Weather> mWeather;
    /* this + 440  */ std::unique_ptr<Seasons> mSeasons;
    /* this + 448  */ std::unique_ptr<GameEventDispatcher> mGameEventDispatcher;
    /* this + 456  */ std::unique_ptr<CircuitSystem> mCircuitSystem;
    /* this + 464  */ const int CIRCUIT_TICK_RATE;
    /* this + 468  */ int mCircuitSystemTickRate;
    /* this + 472  */ std::unordered_map<ActorUniqueID, WeakEntityRef> mActorIDEntityIDMap;
    /* this + 536  */ std::vector<WeakEntityRef> mDisplayEntities;
    /* this + 560  */ std::shared_ptr<WireframeQueue> mWireframeQueue;
    /* this + 576  */ FeatureTerrainAdjustments mFeatureTerrainAdjustments;
    /* this + 684  */ std::unordered_map<ChunkPos, std::vector<std::unique_ptr<CompoundTag>>> mLimboEntities;
    /* this + 712  */ std::set<ActorUniqueID> mEntitiesToMoveChunks;
    /* this + 728  */ std::shared_ptr<TickingAreaList> mTickingAreaList;
    /* this + 744  */ LevelChunkGarbageCollector mLevelChunkGarbageCollector;
    /* this + 1376 */ std::set<ActorUniqueID> mWitherIDs;
    /* this + 1392 */ std::unique_ptr<LevelChunkBuilderData> mLevelChunkBuilderData;
    /* this + 1400 */ std::chrono::steady_clock::time_point mLastPruneTime;
    /* this + 1408 */ std::chrono::steady_clock::time_point mNextPruneTime;
    /* this + 1416 */ std::unique_ptr<ChunkBuildOrderPolicyBase> mChunkBuildOrderPolicy;
    /* this + 1424 */ std::unique_ptr<VillageManager> mVillageManager;
    /* this + 1432 */ std::vector<NetworkIdentifierWithSubId> mTemporaryPlayerIds; 
    /* this + 1456 */ std::unique_ptr<ChunkLoadActionList> mChunkLoadActionList; 
    /* this + 1464 */ std::unique_ptr<DelayActionList> mDelayActionList;
    /* this + 1472 */ std::unordered_map<SubChunkPos, UpdateSubChunkBlocksChangedInfo> mBlocksChangedBySubChunkMap;
    /* this + 1536 */ std::unique_ptr<Dimension::PlayerReplicationStructures> mReplicationStructures;
    /* this + 1544 */ std::vector<WeakEntityRef> mPlayersToReplicate;
    /* this + 1568 */ bool mRunChunkGenWatchDog;

public:
    /**@vIndex {0} */
	virtual ~Dimension();

    /**@vIndex {1} */
	virtual bool isNaturalDimension() const override;

    /**@vIndex {2} */
	virtual DimensionType getDimensionId() const override;

    /**@vIndex {3} */
	virtual void sendPacketForPosition(const BlockPos&, const Packet&, const Player*) override;

    /**@vIndex {4} */
	virtual void flushLevelChunkGarbageCollector() override;

    /**@vIndex {5} */
	virtual void initializeWithLevelStorageManager(class LevelStorageManager&) override;

    /**@vIndex {6} */
	virtual BiomeRegistry& getBiomeRegistry() override;

    /**@vIndex {7} */
	virtual const BiomeRegistry& getBiomeRegistry() const override;

    /**@vIndex {8} */
	virtual Vec3 translatePosAcrossDimension(const Vec3&, DimensionType) const override;

    /**@vIndex {9} */
	virtual void forEachPlayer(std::function<bool(class Player&)> callback) const override;

    /**@vIndex {10} */
	virtual Actor* fetchEntity(ActorUniqueID actorID, bool getRemoved) const override;

    /**@vIndex {11} */
	virtual void init(const br::worldgen::StructureSetRegistry&);

    /**@vIndex {12} */
	virtual void tick();
    
    /**@vIndex {13} */
	virtual void tickRedstone();
    
    /**@vIndex {14} */
	virtual std::unique_ptr<class WorldGenerator> createGenerator(const br::worldgen::StructureSetRegistry&) = 0;
    
    /**@vIndex {15} */
	virtual void upgradeLevelChunk(class ChunkSource& source, class LevelChunk& lc, class LevelChunk& generatedChunk) = 0;
    
    /**@vIndex {16} */
	virtual void fixWallChunk(class ChunkSource&, class LevelChunk&) = 0;
    
    /**@vIndex {17} */
	virtual bool levelChunkNeedsUpgrade(const LevelChunk&) const = 0;
    
    /**@vIndex {18} */
	virtual bool isValidSpawn(int x, int z) const;
    
    /**@vIndex {19} */
	virtual class mce::Color getBrightnessDependentFogColor(const mce::Color& baseColor, float brightness) const;
    
    /**@vIndex {20} */
	virtual bool hasPrecipitationFog() const;
    
    /**@vIndex {21} */
	virtual short getCloudHeight() const;
    
    /**@vIndex {22} */
	virtual class HashedString getDefaultBiome() const;
    
    /**@vIndex {23} */
	virtual bool hasGround() const;
    
    /**@vIndex {24} */
	virtual bool showSky() const;
    
    /**@vIndex {25} */
	virtual class BlockPos getSpawnPos() const;
    
    /**@vIndex {26} */
	virtual int getSpawnYPosition() const;
    
    /**@vIndex {27} */
	virtual bool mayRespawnViaBed(void) const;
    
    /**@vIndex {28} */
	virtual bool isDay() const;
    
    /**@vIndex {29} */
	virtual float getTimeOfDay(int time, float a) const;
    
    /**@vIndex {30} */
	virtual float getSunIntensity(float a, const Vec3& viewVector, float minInfluenceAngle) const;
    
    /**@vIndex {31} */
	virtual bool forceCheckAllNeighChunkSavedStat() const;
    
    /**@vIndex {32} */
	virtual void sendBroadcast(const Packet& packet, class Player* except);
    
    /**@vIndex {33} */
	virtual bool is2DPositionRelevantForPlayer(const BlockPos& position, class Player& player) const;
    
    /**@vIndex {34} */
	virtual bool isActorRelevantForPlayer(class Player& player, const Actor& actor) const;
    
    /**@vIndex {35} */
	virtual class BaseLightTextureImageBuilder* getLightTextureImageBuilder() const;
    
    /**@vIndex {36} */
	virtual const DimensionBrightnessRamp& getBrightnessRamp() const;
    
    /**@vIndex {37} */
	virtual void startLeaveGame();
    
    /**@vIndex {38} */
	virtual std::unique_ptr<class ChunkBuildOrderPolicyBase> _createChunkBuildOrderPolicy();
    
    /**@vIndex {39} */
	virtual void _upgradeOldLimboEntity(class CompoundTag& tag, LimboEntitiesVersion vers) = 0;
    
    /**@vIndex {40} */
	virtual std::unique_ptr<class ChunkSource> _wrapStorageForVersionCompatibility(std::unique_ptr<class ChunkSource> storageSource, StorageVersion levelVersion) = 0;

    /** @vIndex {1} @for {SavedData} */
    virtual void deserialize(const CompoundTag&) override;

    /** @vIndex {2} @for {SavedData} */
    virtual void serialize(CompoundTag&) const override;

    /** @vIndex {4} @for {LevelListener} */
    virtual void onBlockChanged(BlockSource& source, const BlockPos& pos, uint32_t layer, const Block& block, const Block& oldBlock, int updateFlags, const ActorBlockSyncMessage* syncMsg, BlockChangedEventTarget eventTarget, Actor* blockChangeSource) override;

    /** @vIndex {5} @for {LevelListener} */
    virtual void onBrightnessChanged(BlockSource& source, const BlockPos& pos) override;

    /** @vIndex {8} @for {LevelListener} */
    virtual void onBlockEvent(BlockSource& source, int x, int y, int z, int b0, int b1) override;

    /** @vIndex {19} @for {LevelListener} */
    virtual void onChunkLoaded(class ChunkSource& source, class LevelChunk& lc) override;

    /** @vIndex {23} @for {LevelListener} */
    virtual void onLevelDestruction(const std::string& levelId) override;

    /**@asmName {Dimension_ctor}*/
    Dimension(ILevel& level, DimensionType dimId, DimensionHeightRange heightRange, Scheduler& callbackContext, std::string dimensionName);

    BlockSource& getBlockSourceFromMainChunkSource() const;

    const Level& getLevelConst() const;
    Level& getLevel() const;
};

//static_assert(sizeof(Dimension) == 1592);
static_assert(offsetof(Dimension, mHeightRange) == 200);
static_assert(offsetof(Dimension, mBlockSource) == 208);
static_assert(offsetof(Dimension, mName) == 328);
static_assert(offsetof(Dimension, mWitherIDs) == 1376);