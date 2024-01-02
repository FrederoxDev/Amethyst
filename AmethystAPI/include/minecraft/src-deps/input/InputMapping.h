#pragma once
#include <vector>
#include <string>
#include "minecraft/src-deps/input/InputMapping.h"

struct KeyboardKeyBinding {
public:
    std::string buttonName;
    int32_t keyNum;
    FocusImpact focusImpact;
};

class KeyboardInputMapping {
public:
    std::vector<KeyboardKeyBinding> keyBindings;
};