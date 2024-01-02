#pragma once
#include <vector>
#include <stdint.h>
#include "minecraft/src-client/common/client/input/Keymapping.h"

class RemappingLayout {
private:
    uintptr_t** vtable;

public:
    std::vector<Keymapping> mKeymappings;
    std::vector<Keymapping> mDefaultMappings;
};