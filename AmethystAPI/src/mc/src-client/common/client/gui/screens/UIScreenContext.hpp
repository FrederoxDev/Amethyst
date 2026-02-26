#pragma once
#include <cstdint>

#pragma pack(push, 1)
class UIScreenContext {
public:
    /* this + 0  */ const int32_t xm;
    /* this + 4  */ const int32_t ym;
    /* this + 8  */ const float a;
    /* this + 12 */ std::byte padding12[4];
};
#pragma pack(pop)

static_assert(sizeof(UIScreenContext) == 16);
