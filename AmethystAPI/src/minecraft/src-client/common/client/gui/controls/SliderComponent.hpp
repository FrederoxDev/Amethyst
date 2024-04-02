#pragma once
#include "minecraft/src-client/common/client/gui/controls/UIComponent.hpp"
#include <cstddef>
#include <cstdint>

class SliderComponent : public UIComponent {
public:
    /* this + 16 */ std::byte padding16[48];
    /* this + 64 */ float mPercentage;

    // 1.20.71.1 - 40 53 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 48 8B D9 F3 0F 11 4C 24 ? 48 8B 49
    int64_t _updateSliderFromStepSize(int64_t a2, int64_t a3);
};