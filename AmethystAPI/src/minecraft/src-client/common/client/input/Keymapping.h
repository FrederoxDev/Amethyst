#pragma once
#include <string>
#include <vector>

class Keymapping {
public:
    Keymapping(const std::string& actionName, int key, bool allowRemapping = true);
    Keymapping(const std::string& actionName, std::vector<int>& keys, bool allowRemapping = true);
    bool isAltKey();
    bool isAssigned();

public:
    std::string mAction;
    std::vector<int> mKeys;
    bool mAllowRemap;
};