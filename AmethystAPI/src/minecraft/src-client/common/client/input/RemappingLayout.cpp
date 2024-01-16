#include "common/client/input/RemappingLayout.h"

Keymapping RemappingLayout::getKeymappingByAction(const std::string* actionName) const {
    for (auto& keymapping : mKeymappings) {
        if (keymapping.mAction == *actionName) return keymapping;
    }

    return { "", 0 };
}

int RemappingLayout::getAdjustedKey(int key) {
    using function = int(__thiscall*)(RemappingLayout*, int);
    return reinterpret_cast<function>(this->vtable[2])(this, key);
}   