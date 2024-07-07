#pragma once
class UIControl;

class VisualTree {
public:
    std::byte padding[8];
    UIControl* mRootControlName; // this + 8
};
