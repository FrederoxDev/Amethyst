#include "minecraft/src-client/common/client/input/Keymapping.hpp"

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
    if (mKeys.size() == 0) return false;

    // Checks if any of the keys have negative keycodes
    auto it = std::find_if(mKeys.begin(), mKeys.end(), [](int v) { return v < 0; });
    return it != mKeys.end();
}

bool Keymapping::isAssigned() {
    return mKeys[0] != 0;
}