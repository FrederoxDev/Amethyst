#pragma once
#include "minecraft/src-deps/core/utility/NonOwnerPointer.hpp"
#include "minecraft/src/common/world/level/dimension/HeightRange.hpp"
#include "minecraft/src/common/world/level/dimension/IDimension.hpp"
#include "minecraft/src/common/world/level/LevelListener.hpp"
#include "minecraft/src/common/world/level/saveddata/SavedData.hpp"
#include "minecraft/src/common/world/level/dimension/DimensionHeightRange.hpp"
#include "minecraft/src/common/gamerefs/OwnerPtr.hpp"
#include <cstddef>
#include <cstdint>
#include <string>

class BlockSource;
class ILevel;
class Scheduler;

class Dimension : public IDimension, LevelListener, SavedData, Bedrock::EnableNonOwnerReferences, std::enable_shared_from_this<Dimension> {
public:
    /* this + 96  */ std::byte filler96[104];
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

public:
    virtual ~Dimension();
    BlockSource& getBlockSourceFromMainChunkSource() const;

    Dimension(ILevel& level, DimensionType dimId, DimensionHeightRange heightRange, Scheduler& callbackContext, std::string dimensionName);
};

static_assert(offsetof(Dimension, mHeightRange) == 200);