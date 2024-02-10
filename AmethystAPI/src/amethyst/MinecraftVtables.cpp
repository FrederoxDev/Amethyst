#include "amethyst/MinecraftVtables.h"
#include "minecraft/src/common/world/level/block/BlockLegacy.h"

extern "C" void* Item_vtable = nullptr;
extern "C" void* BlockLegacy_vtable = nullptr;
extern "C" void* BlockLegacy_ctor = nullptr;

void InitializeVtablePtrs() {
    Item_vtable = reinterpret_cast<void*>(SlideAddress(0x53C9B70));
    BlockLegacy_vtable = reinterpret_cast<void*>(SlideAddress(0x5407B38));
    BlockLegacy_ctor = reinterpret_cast<void*>(SigScan("48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ? 49 8B F9 48 8B F2"));
}