#pragma once
#include "minecraft/src/common/world/phys/Vec2.hpp"
#include <cstddef>

//struct_size = 0x9E0 is_virtual = False
//    hide_vtable = True
//
//#(Type, Name, Size(in bytes), Offset(in bytes))
//    struct
//    = [("Vec2", "totalScreenSize", 8, 48),
//       ("Vec2", "clientScreenSize", 8, 48 + 8),
//       ("Vec2", "clientUIScreenSize", 8, 48 + 16),
//       ("IClientInstance&", "mClient", 8, 136)]

class ClientInstance;
using IClientInstance = ClientInstance;

#pragma pack(push, 1)
class GuiData {
public:
    /* this + 0    */ std::byte padding0[48];
    /* this + 48   */ Vec2 totalScreenSize;
    /* this + 56   */ Vec2 clientScreenSize;
    /* this + 64   */ Vec2 clientUIScreenSize;
    /* this + 72   */ bool mScreenSizeDataValid;
    /* this + 73   */ std::byte padding73[3];
    /* this + 76   */ float mGuiScale;
    /* this + 80   */ std::byte padding77[106 - 80];
    /* this + 106  */ short mPointerX;
    /* this + 108  */ short mPointerY;
    /* this + 110  */ std::byte padding108[136 - 110];
    /* this + 136  */ IClientInstance& mClient;
    /* this + 144  */ std::byte padding144[2384];
};
#pragma pack(pop)

static_assert(sizeof(GuiData) == 0x9E0);