#pragma once
#include "minecraft/src/common/world/level/dimension/HeightRange.hpp"
#include "minecraft/src/common/gamerefs/OwnerPtr.hpp"
#include <cstddef>
#include <cstdint>
#include <string>

class BlockSource;

class Dimension {

public:
    /* this + 0   */ uintptr_t** vtable;
    /* this + 8   */ std::byte filler8[192];
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
    BlockSource& getBlockSourceFromMainChunkSource() const;
};