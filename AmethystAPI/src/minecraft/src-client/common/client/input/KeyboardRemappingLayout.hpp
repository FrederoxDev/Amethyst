#pragma once
#include <cstdint>
#include <minecraft/src-client/common/client/input/RemappingLayout.hpp>

enum class KeyboardType : int32_t {
    Standard = 0x0000,
    FullKeyboard = 0x0001,
    Count = 0x0002,
};

class KeyboardRemappingLayout : RemappingLayout {
public:
    const KeyboardType mKeyboardType;
};