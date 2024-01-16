#pragma once
#include "common/world/phys/Vec2.h"

#pragma pack(push, 1)
class GuiData {
private:
    char padding0[48];

public:
    Vec2 totalScreenSize;
    Vec2 clientScreenSize;
    Vec2 clientUIScreenSize;
};
#pragma pack(pop)