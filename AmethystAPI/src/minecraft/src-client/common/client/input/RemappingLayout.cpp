#include "minecraft/src-client/common/client/input/RemappingLayout.hpp"

Keymapping RemappingLayout::getKeymappingByAction(const std::string* actionName) const {
    for (auto& keymapping : mKeymappings) {
        if (keymapping.mAction == *actionName) return keymapping;
    }

    return Keymapping("", 0);
}

int RemappingLayout::getAdjustedKey(int key) {
    using function = int(__thiscall*)(RemappingLayout*, int);
    return reinterpret_cast<function>(this->vtable[2])(this, key);
}   