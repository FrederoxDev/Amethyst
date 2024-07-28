#pragma once
#include <minecraft/src/common/world/level/dimension/Dimension.hpp>

/**@vtable */
class OverworldDimension : public Dimension {
public:
    /**
	* @vIndex {0} 
	* @symbol {??1OverworldDimension@@UEAA@XZ}
	*/
	virtual ~OverworldDimension();

	/**@vIndex {8} */
    virtual Vec3 translatePosAcrossDimension(const Vec3&, DimensionType) const override;

    /**@vIndex {14} */
	virtual std::unique_ptr<class WorldGenerator> createGenerator(const br::worldgen::StructureSetRegistry&) override;

    /**@vIndex {15} */
	virtual void upgradeLevelChunk(class ChunkSource& source, class LevelChunk& lc, class LevelChunk& generatedChunk) override;

    /**@vIndex {16} */
	virtual void fixWallChunk(class ChunkSource&, class LevelChunk&) override;

    /**@vIndex {17} */
	virtual bool levelChunkNeedsUpgrade(const LevelChunk&) const override;

	/**@vIndex {19} */
    virtual class mce::Color getBrightnessDependentFogColor(const mce::Color& baseColor, float brightness) const override;

	/**@vIndex {20} */
    virtual bool hasPrecipitationFog() const override;

	/**@vIndex {21} */
    virtual short getCloudHeight() const override;

    /**@vIndex {39} */
	virtual void _upgradeOldLimboEntity(class CompoundTag& tag, LimboEntitiesVersion vers) override;

    /**@vIndex {40} */
	virtual std::unique_ptr<class ChunkSource> _wrapStorageForVersionCompatibility(std::unique_ptr<class ChunkSource> storageSource, StorageVersion levelVersion) override;

	/**@asmName {OverworldDimension_ctor}*/
    OverworldDimension(ILevel& level, Scheduler& callbackContext);

	// made up constructor to set a custom dimID
    OverworldDimension(ILevel& level, DimensionType dimId, DimensionHeightRange heightRange, Scheduler& callbackContext, std::string dimensionName) 
		: Dimension(level, dimId, heightRange, callbackContext, dimensionName) {}
};