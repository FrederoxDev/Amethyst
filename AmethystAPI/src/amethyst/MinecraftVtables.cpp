#include "amethyst/MinecraftVtables.hpp"
#include "minecraft/src/common/world/level/block/BlockLegacy.hpp"
#include "minecraft/src/common/world/item/ItemStack.hpp"
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
extern "C" void* Container_vtable = nullptr;
extern "C" void* FillingContainer_vtable = nullptr;
extern "C" void* RandomizableBlockActorContainerBase_vtable = nullptr;
extern "C" void* Dimension_vtable = nullptr;
extern "C" void* OverworldDimension_vtable = nullptr;
extern "C" void* Dimension_for_SavedData_vtable = nullptr;
extern "C" void* Dimension_for_LevelListener_vtable = nullptr;
extern "C" void* ChunkSource_vtable = nullptr;
extern "C" void* WorldGenerator_vtable = nullptr;
extern "C" void* ActorShaderManager_vtable = nullptr;

// Constructors
extern "C" void* BlockItem_ctor = nullptr;
extern "C" void* BlockLegacy_ctor = nullptr;
extern "C" void* MaterialPtr_ctor = nullptr;
extern "C" void* BlockActor_ctor = nullptr;
extern "C" void* BaseActorRenderer_ctor = nullptr;
extern "C" void* ChestBlock_ctor = nullptr;
extern "C" void* Container_ctor1 = nullptr;
extern "C" void* Container_ctor2 = nullptr;
extern "C" void* Dimension_ctor = nullptr;
extern "C" void* OverworldDimension_ctor = nullptr;
extern "C" void* WorldGenerator_ctor = nullptr;
extern "C" void* StructureFeatureRegistry_ctor = nullptr;
extern "C" void* TextureContainer_ctor = nullptr;

// Static variables
// 1.21.0.3
ItemStack& ItemStack::EMPTY_ITEM = *reinterpret_cast<ItemStack*>(SlideAddress(0x57CF0A0));

//48 89 5C 24 ? 48 89 

void InitializeVtablePtrs()
{
    InitializeVtbl(Item_vtable, "48 8D 05 ? ? ? ? 48 89 01 48 83 C1 ? 0F 57 C0 0F 11 01 4C 89 61 ? 4C 89 61 ? 45 8D 44 24");

    InitializeVtbl(BlockLegacy_vtable, "48 8D 05 ? ? ? ? 49 89 04 24 0F 57 C0 41 0F 11 44 24 ? 49 89 4C 24");
    InitializeCtor(BlockLegacy_ctor, "48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ? 49 8B F9 48 8B F2");

    InitializeVtbl(BlockItem_vtable, "48 8D 05 ? ? ? ? 49 89 06 41 0F B7 8E");
    InitializeCtor(BlockItem_ctor, "40 53 55 56 57 41 56 48 81 EC ? ? ? ? 49 8B F9 48 8B EA");

    InitializeVtbl(BlockActor_vtable, "48 8D 05 ? ? ? ? 4C 89 49 ? 48 89 01 44 89 49");
    InitializeCtor(BlockActor_ctor, "48 83 EC ? 45 33 C9 0F 29 34 24");

    InitializeVtbl(BaseActorRenderer_vtable, "48 8D 05 ? ? ? ? 48 89 01 48 8D 79 ? 48 89 7C 24 ? 0F 57 C0 0F 11 45");
    InitializeCtor(BaseActorRenderer_ctor, "48 89 5C 24 ? 48 89 74 24 ? 55 57 41 54 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 4C 8B F1 48 89 4D ? 45 33 E4 4C 89 61");

    InitializeVtbl(BlockActorRenderer_vtable, "48 8D 05 ? ? ? ? 48 89 06 48 8D 05 ? ? ? ? 48 89 46 ? 40 88 BE");

    InitializeVtbl(Packet_vtable, "48 8D 05 ? ? ? ? 4C 8B CA");

    InitializeVtbl(ChestBlock_vtable, "48 8D 05 ?? ?? ?? ?? 48 89 03 89 BB ?? ?? ?? ?? 48 C7 83");
    InitializeCtor(ChestBlock_ctor, "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B 05 ? ? ? ? 48 8B D9 4C 8B 15");

    InitializeCtor(Container_ctor1, "48 89 5C 24 ? 48 89 4C 24 ? 57 48 83 EC ? 48 8B D9 48 8D 05 ? ? ? ? 48 89 01 88 51");
    InitializeCtor(Container_ctor2, "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 4C 24 ? 57 48 83 EC ? 41 0F B6 F1 49 8B F8 48 8B D9 48 8D 05");
    InitializeVtbl(Container_vtable, "48 8D 05 ? ? ? ? 48 89 03 66 C7 43 ? ? ? 48 8D 4B");

    InitializeVtbl(FillingContainer_vtable, "48 8D 05 ? ? ? ? 49 89 06 49 8D BE ? ? ? ? 33 C0");

    InitializeVtbl(RandomizableBlockActorContainerBase_vtable, "48 8D 05 ? ? ? ? 48 8D 8F ? ? ? ? 48 89 07");

    InitializeVtbl(Dimension_vtable, "48 8D 05 ? ? ? ? 49 89 06 48 8D 05 ? ? ? ? 49 89 46 ? 48 8D 05 ? ? ? ? 49 89 46 ? 48 8D 05 ? ? ? ? 48 89 06");
    InitializeCtor(Dimension_ctor, "48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 55 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 41 8B F9 41 8B D8"); 
    InitializeVtbl(Dimension_for_SavedData_vtable, "48 8D 05 ? ? ? ? 49 89 46 ? 48 8D 05 ? ? ? ? 48 89 06");
    InitializeVtbl(Dimension_for_LevelListener_vtable, "48 8D 05 ? ? ? ? 49 89 46 ? 48 8D 05 ? ? ? ? 49 89 46 ? 48 8D 05 ? ? ? ? 48 89 06");

    InitializeVtbl(OverworldDimension_vtable, "48 8D 05 ? ? ? ? 48 89 06 48 8D 05 ? ? ? ? 48 89 46 ? 48 8D 05 ? ? ? ? 48 89 46 ? 48 8D 05 ? ? ? ? 48 89 46 ? C6 86");
    InitializeCtor(OverworldDimension_ctor, "4C 8B DC 49 89 5B ? 55 56 57 48 83 EC ? 49 8B D8");

    InitializeVtbl(ChunkSource_vtable, "48 8D 05 ? ? ? ? 48 89 07 8B 43 ? 89 47 ? 48 8B 43 ? 48 89 47");

    InitializeVtbl(WorldGenerator_vtable, "48 8D 05 ? ? ? ? 48 89 07 48 8D 05 ? ? ? ? 48 89 47 ? 48 8D 4F ? E8 ? ? ? ? 90 48 8B 06");
    InitializeCtor(WorldGenerator_ctor, "48 89 5C 24 ? 55 56 57 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 49 8B F0 48 8B DA 48 8B F9 48 89 4C 24 ? 4C 89 44 24");

    InitializeCtor(StructureFeatureRegistry_ctor, "48 89 5C 24 ? 48 89 74 24 ? 48 89 4C 24 ? 57 48 83 EC ? 48 8B F9 33 F6 48 89 31 48 89 71 ? 48 89 71 ? 48 89 71 ? 48 89 71 ? 48 89 71 ? 48 89 71 ? 48 89 71 ? 48 89 71 ? 48 8D 59 ? 0F 57 C0");

    InitializeCtor(TextureContainer_ctor, "48 8B C4 48 89 48 ? 53 48 83 EC ? 48 8B D9 33 C9 48 89 0B");
}