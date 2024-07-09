#pragma once
#include <minecraft/src/common/world/level/chunk/ChunkGeneratorStructureState.hpp>
#include <minecraft/src/common/world/level/levelgen/structure/StructureCache.hpp>

/**@vtable*/
class StructureFeatureRegistry {
public:
    std::byte padding0[208];

    /**@asmName {StructureFeatureRegistry_ctor}*/
    StructureFeatureRegistry();

    ~StructureFeatureRegistry(){};
};



    // ChunkGeneratorStructureState mChunkGeneratorStructureState; // 0x0
// std::byte filler30[sizeof(std::vector<int>)];               // 0x30 // This should be a vector of unqiue_ptr<StructureFeature> but I'm too lazy to implement that xD its 1:10 am and I'm tired
// StructureCache mStructureCache;                             // 0x48