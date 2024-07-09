#pragma once
#include <unordered_set>
#include <condition_variable>
#include <minecraft/src-deps/core/utility/buffer_span.hpp>
#include <minecraft/src-deps/core/threading/SpinLock.hpp>
#include <minecraft/src-deps/core/threading/Mutex.hpp>
#include <minecraft/src/common/world/level/ChunkPos.hpp>
#include <minecraft/src/common/world/level/chunk/ChunkSource.hpp>
#include <minecraft/src/common/world/level/levelgen/v1/IPreliminarySurfaceProvider.hpp>
#include <minecraft/src/common/world/level/levelgen/v1/HardcodedSpawnAreaRegistry.hpp>
#include <minecraft/src/common/world/level/levelgen/structure/StructureFeatureType.hpp>
#include <minecraft/src/common/world/level/levelgen/structure/StructureFeatureRegistry.hpp>

/**@vtable*/
class WorldGenerator : public ChunkSource, public IPreliminarySurfaceProvider {
public:
    struct BlockVolumeDimensions {
        uint32_t mWidth;
        uint32_t mDepth;
        uint32_t mHeight;
    };

public:
    /* this + 120 */ std::unique_ptr<HardcodedSpawnAreaRegistry> mHardcodedSpawnAreaRegistry;
    /* this + 128 */ std::unique_ptr<StructureFeatureRegistry> mStructureFeatureRegistry;     
    /* this + 136 */ Bedrock::Threading::Mutex mCreateStructureInstancesMutex;
    /* this + 216 */ std::condition_variable mStructureInstanceWaitVar;
    /* this + 288 */ std::atomic<int> mActiveStructureInstanceCreateCount;
    /* this + 292 */ std::byte visitedPositions[64]; // std::unordered_set<ChunkPos> visitedPositions;
    /* this + 360 */ SpinLock visitedPositionsMutex;

public:
    /**
    * @symbol {??1WorldGenerator@@UEAA@XZ}
    * @vIndex {0} 
    */
    virtual ~WorldGenerator();

    /**@vIndex {12} */
    virtual void postProcessMobsAt(class BlockSource& region, int chunkWestBlock, int chunkNorthBlock, Random& random) override;

    /**@vIndex {33} */
    virtual void init();

    /**@vIndex {34} */
    virtual StructureFeatureType findStructureFeatureTypeAt(class BlockPos const& pos);

    /**@vIndex {35} */
    virtual bool isStructureFeatureTypeAt(class BlockPos const& pos, StructureFeatureType type) const;
    
    /**@vIndex {36} */
    virtual bool findNearestStructureFeature(StructureFeatureType, class BlockPos const&, class BlockPos&, bool, std::optional<class HashedString>);

    /**@vIndex {37} */
    virtual void garbageCollectBlueprints(class buffer_span<class ChunkPos> activeChunks);

    /**@vIndex {38} */
    virtual void prepareHeights(class BlockVolume& box, class ChunkPos const& chunkPos, bool factorInBeardsAndShavers) = 0;
    
    /**@vIndex {39} */
    virtual void prepareAndComputeHeights(class BlockVolume& box, class ChunkPos const& chunkPos, std::vector<short>& ZXheights, bool factorInBeardsAndShavers, int skipTopN) = 0;

    /**@vIndex {40} */
    virtual class BiomeArea getBiomeArea(class BoundingBox const& area, uint32_t scale) const = 0;

    /**@vIndex {41} */
    virtual class BiomeSource const& getBiomeSource() const = 0;

    /**@vIndex {42} */
    virtual struct BlockVolumeDimensions getBlockVolumeDimensions() const = 0;

    /**@vIndex {43} */
    virtual class BlockPos findSpawnPosition() const = 0;

    /**@vIndex {44} */
    virtual void addHardcodedSpawnAreas(class LevelChunk& lc);

    /**@vIndex {45} */
    virtual void debugRender();

    /**@vIndex {46} */
    virtual void decorateWorldGenLoadChunk(
        class Biome const& biome,
        class LevelChunk& lc,
        class BlockVolumeTarget& target,
        class Random& random,
        class ChunkPos const& pos) const = 0;

    /**@vIndex {47} */
    virtual void decorateWorldGenPostProcess(
        class Biome const& biome,
        class LevelChunk& lc,
        class BlockSource& source,
        class Random& random) const = 0;

    // const WorldGenerator::`vftable'{for`IPreliminarySurfaceProvider'}
    // easier to just define this one in c++
    virtual std::optional<short> getPreliminarySurfaceLevel(QuartPos2d worldQuartPos) const override;

    /**@asmName {WorldGenerator_ctor}*/
    WorldGenerator(class Dimension& dimension, std::unique_ptr<StructureFeatureRegistry> structureFeatureRegistry);
};

static_assert(sizeof(WorldGenerator) == 0x188, "WorldGenerator size is incorrect!");
static_assert(offsetof(WorldGenerator, visitedPositionsMutex) == 360);