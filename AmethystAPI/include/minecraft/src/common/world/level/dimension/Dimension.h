#pragma once
#include <stdint.h>

class BlockSource;

class Dimension {
private:
    uintptr_t** vtable;

public:
    BlockSource* getBlockSourceFromMainChunkSource();
};