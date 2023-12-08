#pragma once
#include <stdint.h>
#include "minecraft/src/common/world/level/BlockSource.h"

class Dimension {
private:
    uintptr_t** vtable;

public:
    BlockSource* getBlockSourceFromMainChunkSource();
};