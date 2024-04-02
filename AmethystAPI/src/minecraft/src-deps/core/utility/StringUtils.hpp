#pragma once
#include <string>
#include <algorithm>

namespace Util {
    std::string toLower(const std::string& inString) {
        std::string out = inString;
        std::transform(out.begin(), out.end(), out.begin(), [](unsigned char c){ return std::tolower(c); });
        return out;
    }
}