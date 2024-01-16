#include "core/string/StringHash.h"

bool HashedString::operator==(const HashedString& rhs) const
{
    if (mStrHash == rhs.mStrHash) {
        return mStr == rhs.mStr;
    }

    return false;
}

bool HashedString::operator!=(const HashedString& rhs) const
{
    return !(*this == rhs);
}

bool HashedString::operator<(const HashedString& rhs) const
{
    if (mStrHash == rhs.mStrHash) {
        return mStr < rhs.mStr;
    }
    else if (mStrHash < rhs.mStrHash) {
        return true;
    }
    else {
        return false;
    }
}

HashedString::HashedString(const HashedString& rhs) : HashedString()
{
    mStr = rhs.mStr;
    mStrHash = rhs.mStrHash;
}

HashedString::HashedString(HashedString&& rhs) noexcept : HashedString()
{
    mStr = std::move(rhs.mStr);
    mStrHash = rhs.mStrHash;
}

HashedString::HashedString(std::nullptr_t) : HashedString() {}

HashType64 HashedString::computeHash(const char* str)
{
    if (str) {
        return hash(str);
    }

    return 0;
}

HashType64 HashedString::computeHash(const std::string& str)
{
    if (str.empty()) {
        return 0;
    }

    return computeHash(str.c_str());
}

HashedString::HashedString(const char* str) : HashedString()
{
    mStr = str;
    mStrHash = computeHash(str);
}

HashedString::HashedString(const std::string& str) : HashedString()
{
    mStr = str;
    mStrHash = computeHash(str);
}

HashedString::HashedString(HashType64 hash, const char* str) : HashedString()
{
    mStrHash = hash;
    mStr = str;
}

HashedString::HashedString(HashType64 hash, std::string str) : HashedString()
{
    mStrHash = hash;
    mStr = str;
}

HashedString& HashedString::operator=(const HashedString& rhs)
{
    mStr = rhs.mStr;
    mStrHash = rhs.mStrHash;
    return *this;
}

bool HashedString::isEmpty() const
{
    return mStr.empty();
}

bool HashedString::empty() const
{
    return mStr.empty();
}

void HashedString::clear()
{
    mStr = "";
    mStrHash = 0;
}

HashType64 HashedString::getHash() const
{
    return mStrHash;
}

const std::string& HashedString::getString() const
{
    return mStr;
}

const char* HashedString::c_str() const
{
    return mStr.c_str();
}

const HashedString& HashedString::getEmptyString()
{
    static HashedString emptyString;
    return emptyString;
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