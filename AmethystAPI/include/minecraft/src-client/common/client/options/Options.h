#pragma once
#include <vector>
#include <memory>

class KeyboardRemappingLayout;

class Options {
public:
    bool padding0[5984];
    // Found in Options::_readKeyboardMapping in call to RemappingLayout::setMapping
    std::vector<std::shared_ptr<KeyboardRemappingLayout>> mKeyboardRemappings;
};