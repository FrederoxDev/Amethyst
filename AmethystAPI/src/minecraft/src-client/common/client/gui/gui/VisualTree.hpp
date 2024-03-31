#pragma once
#include "minecraft/src-client/common/client/gui/gui/UIControl.hpp"

class VisualTree {
public:
    std::byte padding[8];
    UIControl* mRootUiControl; // this + 8
};
