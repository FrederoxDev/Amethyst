#pragma once
#include <cstdint>

#pragma pack(push, 8)
class UIScreenContext {
public:
    /* this + 0  */ public: const int32_t xm;
    /* this + 4  */ public: const int32_t ym;
    /* this + 8  */ public: const float a;
    /* this + 12 */ std::byte padding12[4];
};
#pragma pack(pop)

static_assert(sizeof(UIScreenContext) == 16);