#pragma once
#include "minecraft/src-client/common/client/game/MinecraftGame.hpp"
#include "minecraft/src-client/common/client/gui/gui/GuiData.hpp"
#include "minecraft/src-client/common/client/player/LocalPlayer.hpp"
#include "minecraft/src/common/world/level/BlockSource.hpp"
#include <cstdint>
#include "minecraft/src-deps/renderer/Camera.hpp"

class Minecraft;
class ClientInputHandler;
class ItemRenderer;
class BlockTessellator;

//is_virtual = True
//    hide_vtable = False
//        struct_size = 3232
//
//#(Type, Name, Size(in bytes), Offset(in bytes))
//    struct
//    = [("MinecraftGame*", "minecraftGame", 8, 200),
//       ("Minecraft*", "minecraft", 8, 208),
//       ("ClientInputHandler*", "inputHandler", 8, 272),
//       ("ItemRenderer*", "itemRenderer", 8, 1360),
//       ("GuiData*", "guiData", 8, 1368),
//       ("mce::Camera", "camera", 512, 624),
//       ("BlockTessellator*", "mBlockTessellator", 8, 1320)]

#pragma pack(push, 1)
class ClientInstance {
public:
    /* this + 0    */ uintptr_t** vtable;
    /* this + 8    */ std::byte padding8[192];
    /* this + 200  */ MinecraftGame* minecraftGame;
    /* this + 208  */ Minecraft* minecraft;
    /* this + 216  */ std::byte padding216[56];
    /* this + 272  */ ClientInputHandler* inputHandler;
    /* this + 280  */ std::byte padding280[344];
    /* this + 624  */ mce::Camera camera;
    /* this + 1136 */ std::byte padding1136[184];
    /* this + 1320 */ BlockTessellator* mBlockTessellator;
    /* this + 1328 */ std::byte padding1328[32];
    /* this + 1360 */ ItemRenderer* itemRenderer;
    /* this + 1368 */ GuiData* guiData;
    /* this + 1376 */ std::byte padding1376[1856];

public:
    // 1.20.71.1 - 48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 49 8B F9 49 8B D8 4C 8B E2
    ClientInstance(uint64_t a2, uint64_t a3, uint64_t a4, char a5, void* a6, void* a7, uint64_t a8, void* a9);
    // Fake Ctor for hooking.
    void _ClientInstance(uint64_t a2, uint64_t a3, uint64_t a4, char a5, void* a6, void* a7, uint64_t a8, void* a9);

    // 1.20.51.1 - 40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 45 8B F1
    int64_t onStartJoinGame(ClientInstance*, int64_t, int64_t, int64_t);

    // 1.20.51.1 - 48 89 5C 24 ? 48 89 74 24 ? 55 57 41 54 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 45 0F B6 F0 44 0F B6 FA
    void requestLeaveGame(char switchScreen, char sync);

    BlockSource* getRegion();
    LocalPlayer* getLocalPlayer();
};
#pragma pack(pop)

static_assert(sizeof(ClientInstance) == 3232);