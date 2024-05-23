#include "amethyst/MinecraftVtables.hpp"
#include "minecraft/src/common/world/level/block/BlockLegacy.hpp"
#include "minecraft/src-client/common/client/renderer/RenderMaterialGroup.hpp"

extern "C" void* Item_vtable = nullptr;

extern "C" void* BlockItem_vtable = nullptr;
extern "C" void* BlockItem_ctor = nullptr;

extern "C" void* BlockLegacy_vtable = nullptr;
extern "C" void* BlockLegacy_ctor = nullptr;

extern "C" void* MaterialPtr_ctor = nullptr;

extern "C" void* BlockActor_vtable = nullptr;
extern "C" void* BlockActor_ctor = nullptr;

void InitializeVtablePtrs() {
    // 1.20.71.1
    Item_vtable = reinterpret_cast<void*>(AddressFromLeaInstruction(
        SigScan("48 8D 05 ? ? ? ? 48 89 01 48 83 C1 ? 0F 57 C0 0F 11 01 4C 89 61 ? 4C 89 61 ? 45 8D 44 24"))
    );
    
    // 1.20.71.1
    BlockLegacy_vtable = reinterpret_cast<void*>(AddressFromLeaInstruction(
        SigScan("48 8D 05 ? ? ? ? 49 89 04 24 0F 57 C0 41 0F 11 44 24 ? 49 89 4C 24")
    ));
    BlockLegacy_ctor = reinterpret_cast<void*>(SigScan("48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ? 49 8B F9 48 8B F2"));
    
    // 1.20.71.1
    BlockItem_vtable = reinterpret_cast<void*>(AddressFromLeaInstruction(
        SigScan("48 8D 05 ? ? ? ? 48 89 07 0F B7 8F")
    ));
    BlockItem_ctor = reinterpret_cast<void*>(SigScan("48 89 5C 24 ? 48 89 74 24 ? 48 89 4C 24 ? 57 48 83 EC ? 48 8B F2 48 8B F9 E8 ? ? ? ? 90 48 8D 05 ? ? ? ? 48 89 07 0F B7 8F"));

    // 1.20.71.1
    BlockActor_vtable = reinterpret_cast<void*>(AddressFromLeaInstruction(
        SigScan("48 8D 05 ? ? ? ? 4C 89 49 ? 48 89 01 44 89 49"))
    );
    BlockActor_ctor = reinterpret_cast<void*>(SigScan("48 83 EC ? 45 33 C9 0F 29 34 24"));


    // 1.20.51.1
    //MaterialPtr_ctor = reinterpret_cast<void*>(SigScan("48 89 4C 24 ? 53 48 83 EC ? 4C 8B CA 48 8B D9 33 C0"));
}