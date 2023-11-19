#pragma once
#include <stdint.h>
#include "minecraft/common/world/level/BlockSource.h"

class Dimension {
private:
    uintptr_t** vtable;

public:
    const BlockSource* getBlockSourceFromMainChunkSource();
};