#pragma once
#include <string>
#include <vector>

class Keymapping {
public:
    Keymapping(const std::string& actionName, int key, bool allowRemapping = true);
    Keymapping(const std::string& actionName, std::vector<int>& keys, bool allowRemapping = true);
    
    /*Checks if any of the keys assigned have negative keycodes */
    bool isAltKey();

    /* Checks if there are any keys associated with this mapping */
    bool isAssigned();

public:
    std::string mAction;
    std::vector<int> mKeys;
    bool mAllowRemap;
    bool unknown;
};