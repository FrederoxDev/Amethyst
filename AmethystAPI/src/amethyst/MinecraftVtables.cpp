#include "amethyst/MinecraftVtables.hpp"
#include "minecraft/src/common/world/level/block/BlockLegacy.hpp"
#include "minecraft/src-client/common/client/renderer/RenderMaterialGroup.hpp"

// Helper functions
void InitializeCtorImpl(void*& ctorPtr, std::string signature, std::string ctorName)
{
    std::optional<uintptr_t> result = SigScanSafe(signature);

    if (!result.has_value()) {
        Log::Warning("[MinecraftVtables] Failed to find address of '{}' with signature '{}'", ctorName, signature);
        return;
    }

    ctorPtr = reinterpret_cast<void*>(result.value());
}

void InitializeVtblImpl(void*& vtablePtr, std::string signature, std::string vtableName)
{
    std::optional<uintptr_t> result = SigScanSafe(signature);

    if (!result.has_value()) {
        Log::Warning("[MinecraftVtables] Failed to initialize '{}' with signature '{}'", vtableName, signature);
        return;
    }

    uintptr_t addressFromLea = NULL;
    try {
        addressFromLea = AddressFromLeaInstruction(result.value());
    }
    catch (...) {
        Log::Warning("[MinecraftVtables] Signature '{}', for '{}' did not point to an LEA instruction", signature, vtableName);
        return;
    }

    vtablePtr = reinterpret_cast<void*>(addressFromLea);
}

// Vtables
extern "C" void* Item_vtable = nullptr;
extern "C" void* BlockItem_vtable = nullptr;
extern "C" void* BlockLegacy_vtable = nullptr;
extern "C" void* BlockActor_vtable = nullptr;
extern "C" void* BaseActorRenderer_vtable = nullptr;
extern "C" void* BlockActorRenderer_vtable = nullptr;
extern "C" void* Packet_vtable = nullptr;
extern "C" void* ChestBlock_vtable = nullptr;

// Constructors
extern "C" void* BlockItem_ctor = nullptr;
extern "C" void* BlockLegacy_ctor = nullptr;
extern "C" void* MaterialPtr_ctor = nullptr;
extern "C" void* BlockActor_ctor = nullptr;
extern "C" void* BaseActorRenderer_ctor = nullptr;
extern "C" void* ChestBlock_ctor = nullptr;

void InitializeVtablePtrs() {
    InitializeVtbl(Item_vtable, "48 8D 05 ? ? ? ? 48 89 01 48 83 C1 ? 0F 57 C0 0F 11 01 4C 89 61 ? 4C 89 61 ? 45 8D 44 24");
    
    InitializeVtbl(BlockLegacy_vtable, "48 8D 05 ? ? ? ? 49 89 04 24 0F 57 C0 41 0F 11 44 24 ? 49 89 4C 24");
    InitializeCtor(BlockLegacy_ctor, "48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ? 49 8B F9 48 8B F2");

    InitializeVtbl(BlockItem_vtable, "48 8D 05 ? ? ? ? 49 89 06 41 0F B7 8E");
    InitializeCtor(BlockItem_ctor, "40 53 55 56 57 41 56 48 81 EC ? ? ? ? 49 8B F9 48 8B EA");
    
    InitializeVtbl(BlockActor_vtable, "48 8D 05 ? ? ? ? 4C 89 49 ? 48 89 01 44 89 49");
    InitializeCtor(BlockActor_ctor, "48 83 EC ? 45 33 C9 0F 29 34 24");

    InitializeVtbl(BaseActorRenderer_vtable, "48 8D 05 ? ? ? ? 48 89 01 48 8D 79 ? 48 89 7C 24 ? 0F 57 C0 0F 11 45");
    InitializeCtor(BaseActorRenderer_ctor, "48 89 5C 24 ? 48 89 74 24 ? 55 57 41 54 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 4C 8B F1 48 89 4D");

    InitializeVtbl(BlockActorRenderer_vtable, "48 8D 05 ? ? ? ? 48 89 06 48 8D 05 ? ? ? ? 48 89 46 ? 40 88 BE");

    Packet_vtable = (void*)SlideAddress(0x4CB18D0); // 1.21.0.3

    ChestBlock_vtable = (void*)SlideAddress(0x4E37018);
    InitializeCtor(ChestBlock_ctor, "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B 05 ? ? ? ? 48 8B D9 4C 8B 15");
    
    /*InitializeVtbl(Packet_vtable, "48 89 01 F6 C2 ? 74 ? BA ? ? ? ? E8 ? ? ? ? 48 8B C3 48 83 C4 ? 5B C3 CC CC CC CC CC 48 89 5C 24 ? 57 48 83 EC ? 48 8B D9 49 8B F8");
    Log::Info("vtbl 0x{:x}", (uintptr_t)Packet_vtable - GetMinecraftBaseAddress());*/
}