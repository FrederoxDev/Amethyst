#pragma once
#include <vector>
#include <cstdint>
#include "common/client/input/Keymapping.h"

class RemappingLayout {
private:
    uintptr_t** vtable;

public:
    std::vector<Keymapping> mKeymappings;
    std::vector<Keymapping> mDefaultMappings;

    Keymapping getKeymappingByAction(const std::string* actionName) const;

//vfuncs:
    int getAdjustedKey(int); 

//hooks:
    // 48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8B EC 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 4C 8B C2
    typedef void(__thiscall* _assignDefaultMapping)(RemappingLayout*, std::vector<Keymapping>&& mapping);
};