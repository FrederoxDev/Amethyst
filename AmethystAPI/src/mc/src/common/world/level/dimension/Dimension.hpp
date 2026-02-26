/// @symbols
#pragma once
#include <amethyst/Imports.hpp>
#include "mc/src-deps/core/threading/Mutex.hpp"
#include <mc/src/common/world/level/chunk/ChunkSource.hpp>
#include "mc/src/common/world/level/dimension/DimensionHeightRange.hpp"
#include "mc/src/common/world/level/dimension/IDimension.hpp"
#include "mc/src/common/world/level/LevelListener.hpp"
#include "mc/src/common/world/level/saveddata/SavedData.hpp"
#include "mc/src/common/world/level/Level.hpp"
#include "mc/src/common/world/level/storage/StorageVersion.hpp"
#include "mc/src/common/world/level/ChunkPos.hpp"
#include "mc/src/common/world/level/chunk/LevelChunkGarbageCollector.hpp"
#include "mc/src/common/world/level/levelgen/v1/FeatureTerrainAdjustments.hpp"
#include "mc/src/common/world/level/levelgen/structure/StructureSetRegistry.hpp"
#include <mc/src-deps/core/threading/TaskGroup.hpp>


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

/** @vptr {0x4E5FB08} */
/** @vptr {0x4E5FA10, SavedData} */
/** @vptr {0x4E5FA28, LevelListener} */
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
    /**@vidx {0} */
	MC virtual ~Dimension();

    /**@vidx {i} */
	MC virtual bool isNaturalDimension() const override;

    /**@vidx {i} */
	MC virtual DimensionType getDimensionId() const override;

    /**@vidx {i} */
	MC virtual void sendPacketForPosition(const BlockPos&, const Packet&, const Player*) override;

    /**@vidx {i} */
	MC virtual void flushLevelChunkGarbageCollector() override;

    /**@vidx {i} */
	MC virtual void initializeWithLevelStorageManager(class LevelStorageManager&) override;

    /**@vidx {i} */
	MC virtual BiomeRegistry& getBiomeRegistry() override;

    /**@vidx {i} */
	MC virtual const BiomeRegistry& getBiomeRegistry() const override;

    /**@vidx {i} */
	MC virtual Vec3 translatePosAcrossDimension(const Vec3&, DimensionType) const override;

    /**@vidx {i} */
	MC virtual void forEachPlayer(std::function<bool(class Player&)> callback) const override;

    /**@vidx {i} */
	MC virtual Actor* fetchEntity(ActorUniqueID actorID, bool getRemoved) const override;

    /**@vidx {11} */
	MC virtual void init(const br::worldgen::StructureSetRegistry&);

    /**@vidx {12} */
	MC virtual void tick();
    
    /**@vidx {13} */
	MC virtual void tickRedstone();
    
    /**@vidx {14} */
	MC virtual std::unique_ptr<class WorldGenerator> createGenerator(const br::worldgen::StructureSetRegistry&) = 0;
    
    /**@vidx {15} */
	MC virtual void upgradeLevelChunk(class ChunkSource& source, class LevelChunk& lc, class LevelChunk& generatedChunk) = 0;
    
    /**@vidx {16} */
	MC virtual void fixWallChunk(class ChunkSource&, class LevelChunk&) = 0;
    
    /**@vidx {17} */
	MC virtual bool levelChunkNeedsUpgrade(const LevelChunk&) const = 0;
    
    /**@vidx {18} */
	MC virtual bool isValidSpawn(int x, int z) const;
    
    /**@vidx {19} */
	MC virtual class mce::Color getBrightnessDependentFogColor(const mce::Color& baseColor, float brightness) const;
    
    /**@vidx {20} */
	MC virtual bool hasPrecipitationFog() const;
    
    /**@vidx {21} */
	MC virtual short getCloudHeight() const;
    
    /**@vidx {22} */
	MC virtual class HashedString getDefaultBiome() const;
    
    /**@vidx {23} */
	MC virtual bool hasGround() const;
    
    /**@vidx {24} */
	MC virtual bool showSky() const;
    
    /**@vidx {25} */
	MC virtual class BlockPos getSpawnPos() const;
    
    /**@vidx {26} */
	MC virtual int getSpawnYPosition() const;
    
    /**@vidx {27} */
	MC virtual bool mayRespawnViaBed(void) const;
    
    /**@vidx {28} */
	MC virtual bool isDay() const;
    
    /**@vidx {29} */
	MC virtual float getTimeOfDay(int time, float a) const;
    
    /**@vidx {30} */
	MC virtual float getSunIntensity(float a, const Vec3& viewVector, float minInfluenceAngle) const;
    
    /**@vidx {31} */
	MC virtual bool forceCheckAllNeighChunkSavedStat() const;
    
    /**@vidx {32} */
	MC virtual void sendBroadcast(const Packet& packet, class Player* except);
    
    /**@vidx {33} */
	MC virtual bool is2DPositionRelevantForPlayer(const BlockPos& position, class Player& player) const;
    
    /**@vidx {34} */
	MC virtual bool isActorRelevantForPlayer(class Player& player, const Actor& actor) const;
    
    /**@vidx {35} */
	MC virtual class BaseLightTextureImageBuilder* getLightTextureImageBuilder() const;
    
    /**@vidx {36} */
	MC virtual const DimensionBrightnessRamp& getBrightnessRamp() const;
    
    /**@vidx {37} */
	MC virtual void startLeaveGame();
    
    /**@vidx {38} */
	MC virtual std::unique_ptr<class ChunkBuildOrderPolicyBase> _createChunkBuildOrderPolicy();
    
    /**@vidx {39} */
	MC virtual void _upgradeOldLimboEntity(class CompoundTag& tag, LimboEntitiesVersion vers) = 0;
    
    /**@vidx {40} */
	MC virtual std::unique_ptr<class ChunkSource> _wrapStorageForVersionCompatibility(std::unique_ptr<class ChunkSource> storageSource, StorageVersion levelVersion) = 0;

    /** @vidx {1, SavedData} */
    MC virtual void deserialize(const CompoundTag&) override;

    /** @vidx {2, SavedData} */
    MC virtual void serialize(CompoundTag&) const override;

    /** @vidx {4, LevelListener}  */
    MC virtual void onBlockChanged(BlockSource& source, const BlockPos& pos, uint32_t layer, const Block& block, const Block& oldBlock, int updateFlags, const ActorBlockSyncMessage* syncMsg, BlockChangedEventTarget eventTarget, Actor* blockChangeSource) override;

    /** @vidx {5, LevelListener} */
    MC virtual void onBrightnessChanged(BlockSource& source, const BlockPos& pos) override;

    /** @vidx {8, LevelListener} */
    MC virtual void onBlockEvent(BlockSource& source, int x, int y, int z, int b0, int b1) override;

    /** @vidx {19, LevelListener} */
    MC virtual void onChunkLoaded(class ChunkSource& source, class LevelChunk& lc) override;

    /** @vidx {23, LevelListener} */
    MC virtual void onLevelDestruction(const std::string& levelId) override;

    /// @signature {48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 55 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 41 8B F9 41 8B D8}
    MC Dimension(ILevel& level, DimensionType dimId, DimensionHeightRange heightRange, Scheduler& callbackContext, std::string dimensionName);

    /// @signature {48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 55 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 41 8B F9 41 8B D8}
    MC Dimension* $ctor(ILevel& level, DimensionType dimId, DimensionHeightRange heightRange, Scheduler& callbackContext, std::string dimensionName);

	/**
	 * Returns the BlockSource used by the main ChunkSource of this Dimension.
	 */
    BlockSource& getBlockSource();

	/**
	 * Returns the BlockSource used by the main ChunkSource of this Dimension.
	 */
	const BlockSource& getBlockSource() const;

    const Level& getLevelConst() const;
    Level& getLevel() const;

	bool isClientSide() const {
		return mLevel->isClientSide();
	}

	bool destroyBlock(const BlockPos& pos, bool dropResources) {
		return mLevel->destroyBlock(*mBlockSource, pos, dropResources);
	}

};

//static_assert(sizeof(Dimension) == 1592);
static_assert(offsetof(Dimension, mHeightRange) == 200);
static_assert(offsetof(Dimension, mBlockSource) == 208);
static_assert(offsetof(Dimension, mName) == 328);
static_assert(offsetof(Dimension, mWitherIDs) == 1376);