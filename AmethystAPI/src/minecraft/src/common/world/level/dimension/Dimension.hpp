#pragma once
#include "minecraft/src/common/world/level/dimension/HeightRange.hpp"
#include <cstddef>
#include <cstdint>
#include <string>

class BlockSource;

class Dimension {
private:
    uintptr_t** vtable;

public:
    std::byte filler0[192];
    HeightRange mHeightRange;
    /**
     * @note Minecraft's default Dimension constructor seems to set the mSeaLevel to 63
     */
    int16_t mSeaLevel;
    std::byte filler1[122];
    std::string mName;
    uint8_t mId;
    bool mUltraWarm;
    bool mHasCeiling;
    bool mHasWeather;
    bool mHasSkylight;

public:
    BlockSource* getBlockSourceFromMainChunkSource();
};