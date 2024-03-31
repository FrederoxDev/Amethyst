#pragma once
#include <string>
#include "glm/glm.hpp"
#include "minecraft/src/common/world/phys/Vec2.h"
#include <memory>
#include <vector>

class UIPropertyBag;

class UIControl {
public:
    /* this + 0   */ uintptr_t** vtable;
    /* this + 8   */ std::byte padding8[16];
    /* this + 24  */ std::string mName; // +8 string size
    /* this + 56  */ glm::tvec2<float> mParentRelativePosition;
    /* this + 64  */ glm::tvec2<float> mSize;
    /* this + 72  */ glm::tvec2<float> mMinSize;
    /* this + 80  */ glm::tvec2<float> mMaxSize;
    /* this + 88  */ float mAlpha;
    /* this + 92  */ uint32_t mZOrder;
    /* this + 96  */ uint32_t mLayer;
    /* this + 100 */ Vec2 mClipOffset;
    /* this + 108 */ std::byte padding108[12];
    /* this + 120 */ uint32_t mClipChangeEventId; 
    /* this + 124 */ std::byte padding124[4];  
    /* this + 128 */ std::unique_ptr<UIPropertyBag> mPropertyBag;
    /* this + 136 */ std::weak_ptr<UIControl> mParent;
    /* this + 152 */ std::byte padding152[8]; // +8 idk
    /* this + 160 */ std::vector<std::shared_ptr<UIControl>> mChildren; 
};

static_assert(offsetof(UIControl, mChildren) == 160);
