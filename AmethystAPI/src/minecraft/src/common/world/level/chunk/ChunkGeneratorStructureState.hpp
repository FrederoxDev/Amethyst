#pragma once
#include <cstddef>
#include <cstdint>
#include <vector>

struct ChunkGeneratorStructureState {
public:
    uint64_t mSeed64;            // this+0x0
    uint64_t mSeed;              // this+0x8
    size_t mStructureSetMapSize; // this+0x10
    std::byte filler0[sizeof(std::vector<int>)];     // this+0x18
};