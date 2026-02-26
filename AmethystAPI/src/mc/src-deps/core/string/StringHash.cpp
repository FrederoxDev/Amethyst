#include "mc/src-deps/core/string/StringHash.hpp"

int32_t StringToNameId(const std::string& str)
{
    int hashed = -2128831035;

    for (char c : str) {
        hashed = 16777619 * (hashed ^ c);
    }

    return hashed;
}

bool StringKey::operator==(const StringKey& rha) const
{
    if (getHash() == rha.getHash()) {
        if (mMatch == &rha) {
            mMatch = nullptr;
            rha.mMatch = nullptr;
            return true;
        }
        if (HashedString(*this) == HashedString(rha)) {
            mMatch = &rha;
            rha.mMatch = this;
            return true;
        }
    }

    mMatch = nullptr;
    return false;
}