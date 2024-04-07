#pragma once
#include <cstdint>

class UIControl;

class UIComponent {
public:
    /* this + 0 */ uintptr_t** vtable;
    /* this + 8 */ UIControl& mOwner;
};