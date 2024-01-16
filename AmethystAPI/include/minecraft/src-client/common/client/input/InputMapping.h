#pragma once

#include "common/client/input/InputMapping.h"

#include <string>
#include <vector>

struct KeyboardKeyBinding {
public:
    std::string buttonName;
    int32_t keyNum;
    FocusImpact focusImpact;

    KeyboardKeyBinding(const std::string* buttonName, int32_t key, FocusImpact focus)
    {
        this->buttonName = *buttonName;
        this->keyNum = key;
        this->focusImpact = focus;
    }
};

class KeyboardInputMapping {
public:
    std::vector<KeyboardKeyBinding> keyBindings;
};

class MouseButtonBinding {
    std::string buttonName;
    int buttonNum;

public:
    MouseButtonBinding(const std::string* name, int key)
    {
        buttonName = *name;
        buttonNum = key;
    }
};

class MouseInputMapping {
public:
    std::vector<MouseButtonBinding> buttonBindings;
};