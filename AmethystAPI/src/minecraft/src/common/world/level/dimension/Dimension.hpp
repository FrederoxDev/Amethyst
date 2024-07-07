#pragma once
#include <minecraft/src/common/world/level/chunk/ChunkSource.hpp>
#include "minecraft/src-deps/core/utility/NonOwnerPointer.hpp"
#include "minecraft/src/common/world/level/dimension/HeightRange.hpp"
#include "minecraft/src/common/world/level/dimension/IDimension.hpp"
#include "minecraft/src/common/world/level/LevelListener.hpp"
#include "minecraft/src/common/world/level/saveddata/SavedData.hpp"
#include "minecraft/src/common/gamerefs/OwnerPtr.hpp"
#include "minecraft/src/common/world/level/Level.hpp"
#include "minecraft/src/common/world/level/storage/StorageVersion.hpp"
#include <cstddef>
#include <cstdint>
#include <string>

namespace mce {
class Color;
}
class BlockSource;
class ILevel;
class Scheduler;
class DimensionHeightRange;
class DimensionBrightnessRamp;

enum class LimboEntitiesVersion : char {
    v0,
    v1_8_0,
    v1_10_0,
    v1_12_0,
    v1_16_210
};

namespace br {
namespace worldgen {
class StructureSetRegistry;
}
}

/**@vtable */
class Dimension : public IDimension, public LevelListener, public SavedData, public Bedrock::EnableNonOwnerReferences, public std::enable_shared_from_this<Dimension> {
public:
    /* this + 104 */ std::byte filler104[16];
    /* this + 120 */ Level* mLevel;
    /* this + 128 */ std::byte filler128[72];
    /* this + 200 */ HeightRange mHeightRange;
    /* this + 204 */ int16_t mSeaLevel;
    /* this + 206 */ std::byte padding206[2];
    /* this + 208 */ OwnerPtr<BlockSource> mBlockSource;
    /* this + 224 */ std::byte filler224[104];
    /* this + 328 */ std::string mName;
    /* this + 360 */ uint8_t mId;
    /* this + 361 */ bool mUltraWarm;
    /* this + 362 */ bool mHasCeiling;
    /* this + 363 */ bool mHasWeather;
    /* this + 364 */ bool mHasSkylight;
    /* this + 365 */ std::byte padding365[1592 - 365];

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
};

static_assert(sizeof(Dimension) == 1592);
static_assert(offsetof(Dimension, mHeightRange) == 200);
