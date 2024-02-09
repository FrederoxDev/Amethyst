#include "amethyst/MinecraftVtables.h"
#include "minecraft/src/common/world/level/block/BlockLegacy.h"

extern "C" void* Item_vtable = nullptr;
extern "C" void* BlockLegacy_vtable = nullptr;

void InitializeVtablePtrs() {
    Item_vtable = reinterpret_cast<void*>(SlideAddress(0x53C9B70));
    BlockLegacy_vtable = reinterpret_cast<void*>(SlideAddress(0x5407B38));
}