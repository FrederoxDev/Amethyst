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

extern "C" void* ActorShaderManager_vtable = nullptr;

extern "C" void* BaseActorRenderer_ctor = nullptr;

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

void InitializeVtablePtrs() {
    // 1.20.71.1
    InitializeVtbl(Item_vtable, "48 8D 05 ? ? ? ? 48 89 01 48 83 C1 ? 0F 57 C0 0F 11 01 4C 89 61 ? 4C 89 61 ? 45 8D 44 24");
    
    // 1.20.71.1
    InitializeVtbl(BlockLegacy_vtable, "48 8D 05 ? ? ? ? 49 89 04 24 0F 57 C0 41 0F 11 44 24 ? 49 89 4C 24");
    InitializeCtor(BlockLegacy_ctor, "48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ? 49 8B F9 48 8B F2");

    // 1.20.71.1
    InitializeVtbl(BlockItem_vtable, "48 8D 05 ? ? ? ? 48 89 07 0F B7 8F");
    InitializeCtor(BlockItem_ctor, "48 89 5C 24 ? 48 89 74 24 ? 48 89 4C 24 ? 57 48 83 EC ? 48 8B F2 48 8B F9 E8 ? ? ? ? 90 48 8D 05 ? ? ? ? 48 89 07 0F B7 8F");

    // 1.20.71.1
    InitializeVtbl(BlockActor_vtable, "48 8D 05 ? ? ? ? 4C 89 49 ? 48 89 01 44 89 49");
    InitializeCtor(BlockActor_ctor, "48 83 EC ? 45 33 C9 0F 29 34 24");

    InitializeVtbl(ActorShaderManager_vtable, "FF EE FF EE FF EE FF EE DD DD EE EE");
}