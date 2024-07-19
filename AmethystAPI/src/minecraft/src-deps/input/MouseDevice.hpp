#pragma once

class MouseDevice {
public:
    // 1.21.0.3 - 48 8B C4 48 89 58 ? 48 89 68 ? 48 89 70 ? 57 41 54 41 55 41 56 41 57 48 83 EC ? 44 0F B7 BC 24
    void feed(char actionButtonId, char buttonData, short x, short y, short dx, short dy, bool forceMotionlessPointer);
};