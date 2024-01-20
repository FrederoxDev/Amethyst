#pragma once
#include "minecraft/src/common/world/phys/Vec2.h"

#include <cstddef>

#pragma pack(push, 1)
class GuiData {
private:
    std::byte padding0[48];

public:
    Vec2 totalScreenSize;
    Vec2 clientScreenSize;
    Vec2 clientUIScreenSize;
};
#pragma pack(pop)