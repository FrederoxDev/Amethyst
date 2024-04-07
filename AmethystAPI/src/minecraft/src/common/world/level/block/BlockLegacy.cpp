#include "minecraft/src/common/world/level/block/BlockLegacy.hpp"


BlockLegacy::~BlockLegacy() {

}

short BlockLegacy::getBlockItemId()
{
    // Re-Implemented
    short value = this->mID;
    short result = 255 - value;

    if (value <= 0xFF) {
        return this->mID;
    }

    return result;
}
