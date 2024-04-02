#include "minecraft/src-deps/core/string/StringHash.hpp"

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