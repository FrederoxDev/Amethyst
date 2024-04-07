#pragma once
#include "minecraft/src-client/common/client/gui/controls/UIComponent.hpp"
#include <cstddef>
#include <cstdint>

class ToggleComponent : public UIComponent {
public:
    /* this + 16  */ std::byte padding16[128];
    /* this + 144 */ bool mChecked : 1;
    /* this + 144 */ bool mHover : 1;

    // 1.20.71.1 - 48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B F9 0F B6 81
    int64_t setChecked(int64_t checked, int64_t a3);
};