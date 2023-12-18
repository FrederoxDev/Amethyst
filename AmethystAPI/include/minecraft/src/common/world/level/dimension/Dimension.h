#pragma once
#include "minecraft/src/common/world/level/BlockSource.h"
#include <stdint.h>

class Dimension {
private:
    uintptr_t** vtable;

public:
    BlockSource* getBlockSourceFromMainChunkSource();
};