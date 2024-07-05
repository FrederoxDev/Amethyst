#pragma once
#include <minecraft/src/common/world/level/chunk/ChunkSource.hpp>
#include <minecraft/src/common/world/level/levelgen/v1/IPreliminarySurfaceProvider.hpp>
#include <minecraft/src-deps/core/threading/SpinLock.hpp>
#include <minecraft/src-deps/core/utility/buffer_span.hpp>
#include <minecraft/src/common/world/level/levelgen/structure/StructureFeatureType.hpp>

class WorldGenerator : public ChunkSource, public IPreliminarySurfaceProvider 
{
public:
    struct BlockVolumeDimensions {
        uint32_t mWidth;  // this+0x0
        uint32_t mDepth; // this+0x4
        uint32_t mHeight; // this+0x8
    };
    class HardcodedSpawnAreaRegistry
    {
    public:
        std::byte pad1[0x40]; // Make error go away
    };
    class StructureFeatureRegistry
    {
    public:
        std::byte pad1[0xD0];
    }; // Make error go away

public:
    std::unique_ptr<HardcodedSpawnAreaRegistry> mHardcodedSpawnAreaRegistry; // 0x78
    std::unique_ptr<StructureFeatureRegistry> mStructureFeatureRegistry; // 0x80
    std::byte pad[224]; // 0x88
    SpinLock mSpinLock; // 0x168
    // There is an unordered_map that takes u64 as key and has a shared_ptr of vectors of ItemInstances as value. Above the spinlock
public:
    WorldGenerator(class Dimension& dimension, std::unique_ptr<StructureFeatureRegistry> structureFeatureRegistry);

    virtual ~WorldGenerator();

    /**@vIndex {33} */
    virtual void init();
    /**@vIndex {34} */
    virtual StructureFeatureType findStructureFeatureTypeAt(class BlockPos const& pos);

    /**@vIndex {35} */
    virtual bool isStructureFeatureTypeAt(class BlockPos const& pos, StructureFeatureType type) const;

    
    /**@vIndex {36} */
    virtual bool
    findNearestStructureFeature(StructureFeatureType, class BlockPos const&, class BlockPos&, bool, std::optional<class HashedString>);

    /**@vIndex {37} */
    virtual void garbageCollectBlueprints(class buffer_span<class ChunkPos> activeChunks);


    /**@vIndex {38} */
    virtual void
    prepareHeights(class BlockVolume& box, class ChunkPos const& chunkPos, bool factorInBeardsAndShavers) = 0;
    /**@vIndex {39} */
    virtual void prepareAndComputeHeights(
        class BlockVolume& box,
        class ChunkPos const& chunkPos,
        std::vector<short>& ZXheights,
        bool factorInBeardsAndShavers,
        int skipTopN) = 0;
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

    // IPreliminarySurfaceProvider vtable overloaded functions
    // symbol: ?getPreliminarySurfaceLevel@WorldGenerator@@UEBA?AV?$optional@F@std@@V?$DividedPos2d@$03@@@Z
    virtual std::optional<short> getPreliminarySurfaceLevel(class DividedPos2d<4> worldPos) const;

    // ChunkSource vtable overloaded function
    // symbol: ?postProcessMobsAt@WorldGenerator@@UEAAXAEAVBlockSource@@HHAEAVRandom@@@Z
    virtual void
    postProcessMobsAt(class BlockSource& blockSource, int chunkWestBlock, int chunkNorthBlock, class Random& random);
};

static_assert(sizeof(WorldGenerator) == 0x188, "WorldGenerator size is incorrect!");