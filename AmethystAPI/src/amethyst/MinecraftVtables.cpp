#include "amethyst/MinecraftVtables.h"

extern "C" void* Item_vtable = nullptr;

void InitializeVtablePtrs() {
    Item_vtable = reinterpret_cast<void*>(SlideAddress(0x53C9B70));
}