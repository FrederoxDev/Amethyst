#include "amethyst/MinecraftVtables.hpp"
#include "minecraft/src/common/world/level/block/BlockLegacy.hpp"
#include "minecraft/src-client/common/client/renderer/RenderMaterialGroup.hpp"

extern "C" void* Item_vtable = nullptr;

extern "C" void* BlockItem_vtable = nullptr;
extern "C" void* BlockItem_ctor = nullptr;

extern "C" void* BlockLegacy_vtable = nullptr;
extern "C" void* BlockLegacy_ctor = nullptr;

extern "C" void* MaterialPtr_ctor = nullptr;

void InitializeVtablePtrs() {
    Item_vtable = reinterpret_cast<void*>(SlideAddress(0x53C9B70));
    
    BlockLegacy_vtable = reinterpret_cast<void*>(SlideAddress(0x5407B38));
    BlockLegacy_ctor = reinterpret_cast<void*>(SigScan("48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ? 49 8B F9 48 8B F2"));
    
    BlockItem_vtable = reinterpret_cast<void*>(SlideAddress(0x53EC3D0));
    BlockItem_ctor = reinterpret_cast<void*>(SigScan("48 89 5C 24 ? 48 89 74 24 ? 48 89 4C 24 ? 57 48 83 EC ? 48 8B F2 48 8B F9 E8 ? ? ? ? 90 48 8D 05"));

    MaterialPtr_ctor = reinterpret_cast<void*>(SigScan("48 89 4C 24 ? 53 48 83 EC ? 4C 8B CA 48 8B D9 33 C0"));
}