#pragma once
#include <vector>
#include <memory>
#include <minecraft/src-client/common/client/input/RemappingLayout.hpp>

using KeyboardRemappingLayout = RemappingLayout;

class Options {
public:
    /* this + 0    */ std::byte padding0[6112];
    /* this + 6112 */ std::vector<std::shared_ptr<KeyboardRemappingLayout>> mKeyboardRemappings;

    void* _readKeyboardMapping(char* a2, char* a3);
};