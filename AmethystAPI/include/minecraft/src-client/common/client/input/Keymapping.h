#pragma once
#include <string>
#include <vector>

struct Keymapping {
public:
    std::string mAction;
    std::vector<int> mKeys;
    bool mAllowRemap;
};