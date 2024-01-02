#pragma once
#include <string>
#include <vector>

class Keymapping {
public:
    std::string mAction;
    std::vector<int> mKeys;
    bool mAllowRemap;
};