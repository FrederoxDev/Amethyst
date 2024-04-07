#include "minecraft/src-deps/minecraftrenderer/renderer/Mesh.hpp"
#include <amethyst/Memory.hpp>

void mce::Mesh::renderMesh(mce::MeshContext* meshContext, const mce::MaterialPtr *materialPtr) {
    // 1.20.71.1
    using function = decltype(&mce::Mesh::renderMesh);
    static auto func = std::bit_cast<function>(SigScan("48 89 5C 24 ? 48 89 74 24 ? 57 48 81 EC ? ? ? ? 49 8B D8 C6 44 24")); 
    (this->*func)(meshContext, materialPtr);
}
