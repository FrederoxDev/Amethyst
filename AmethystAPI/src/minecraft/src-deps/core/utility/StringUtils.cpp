#include <minecraft/src-deps/core/utility/StringUtils.hpp>
#include <algorithm>
#include <cctype>

std::string Util::toLower(const std::string& inString)
{
    std::string out = inString;
    std::transform(out.begin(), out.end(), out.begin(), [](unsigned char c) { return std::tolower(c); });
    return out;
}
