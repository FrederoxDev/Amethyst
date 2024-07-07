#include <amethyst/Memory.hpp>
#include <minecraft/src/common/world/level/levelgen/WorldGenerator.hpp>
WorldGenerator::WorldGenerator(Dimension& dimension, std::unique_ptr<StructureFeatureRegistry> structureFeatureRegistry) : ChunkSource((Dimension*)&dimension, 16) {
    using fn = void(__fastcall*)(WorldGenerator*, Dimension&, std::unique_ptr<StructureFeatureRegistry>);

    static fn ctor = (fn)SigScan("48 89 5C 24 ? 55 56 57 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 49 8B F0 48 8B DA 48 8B F9 48 89 4C 24 ? 4C 89 44 24");
    ctor(this, dimension, std::move(structureFeatureRegistry));
}