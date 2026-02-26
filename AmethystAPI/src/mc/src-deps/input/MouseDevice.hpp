/// @symbols
#pragma once
#include <amethyst/Imports.hpp>

class MouseDevice {
public:
    MC void feed(char actionButtonId, char buttonData, short x, short y, short dx, short dy, bool forceMotionlessPointer);
}; 