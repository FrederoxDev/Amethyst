#include "minecraft/src-deps/minecraftrenderer/renderer/Mesh.hpp"
#include <amethyst/Memory.hpp>

void mce::Mesh::renderMesh(mce::MeshContext& meshContext, const mce::MaterialPtr& materialPtr) {
    // 1.20.71.1
    using function = void(mce::Mesh::*)(mce::MeshContext&, const mce::MaterialPtr&);
    static auto func = std::bit_cast<function>(SigScan("48 89 5C 24 ? 48 89 74 24 ? 57 48 81 EC ? ? ? ? 49 8B D8 C6 44 24")); 
    (this->*func)(meshContext, materialPtr);
}

void mce::Mesh::renderMesh(mce::MeshContext& meshContext, const mce::MaterialPtr& materialPtr, const std::variant<std::monostate, mce::TexturePtr, mce::ClientTexture, mce::ServerTexture>& texture)
{
    // 1.20.72.1 - found by xref mce::Mesh::_renderMesh()
    using function = void(mce::Mesh::*)(mce::MeshContext&, const mce::MaterialPtr&, const std::variant<std::monostate, mce::TexturePtr, mce::ClientTexture, mce::ServerTexture>&);
    static auto func = std::bit_cast<function>(SigScan("40 53 56 57 48 81 EC ? ? ? ? 48 8B D9 C6 44 24"));
    (this->*func)(meshContext, materialPtr, texture);
}