#pragma once
#include <cstdint>

class BlockSource;

class Dimension {
private:
    uintptr_t** vtable;

public:
    BlockSource* getBlockSourceFromMainChunkSource();
};