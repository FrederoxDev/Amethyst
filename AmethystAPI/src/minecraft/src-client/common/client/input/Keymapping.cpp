#include "common/client/input/Keymapping.h"

Keymapping::Keymapping(const std::string& actionName, int key, bool allowRemapping) {
    mAction = actionName;
    mKeys = { key };
    mAllowRemap = allowRemapping;
}

Keymapping::Keymapping(const std::string& actionName, std::vector<int>& keys, bool allowRemapping) {
    mAction = actionName;
    mKeys = keys;
    mAllowRemap = allowRemapping;
}

bool Keymapping::isAltKey() {
    for (auto& key : mKeys) {
        if (key < 0) return true;   
    }

    return false;
}

bool Keymapping::isAssigned() {
    return mKeys[0] != 0;
}