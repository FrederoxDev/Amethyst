#pragma once
#include <cstdint>

#pragma pack(push, 8)
class UIScreenContext {
public:
    /* 0x0000 */ public: const int32_t xm;
    /* 0x0004 */ public: const int32_t ym;
    /* 0x0008 */ public: const float a;
    std::byte padding[4];
};
#pragma pack(pop)