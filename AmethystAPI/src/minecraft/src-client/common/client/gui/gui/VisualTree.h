#pragma once
#include "minecraft/src-client/common/client/gui/gui/UIControl.h"

class VisualTree {
public:
    std::byte padding[8];
    UIControl* mRootControlName; // this + 8
};
