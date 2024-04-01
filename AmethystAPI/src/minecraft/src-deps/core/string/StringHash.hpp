#pragma once
#include "minecraft/src-deps/core/headerIncludes/gsl_includes.hpp"
#include <string>

typedef uint64_t HashType64;

class HashedString {
public:
    static HashedString defaultErrorValue;
    const static HashedString EMPTY;

private:
    HashType64 mStrHash{};
    std::string mStr;
    mutable const HashedString* mLastMatch{};

public:
    constexpr HashedString() = default;
    constexpr HashedString(std::nullptr_t) {}

    constexpr HashedString(const HashedString& o) : mStrHash(o.mStrHash), mStr(o.mStr) {}
    constexpr HashedString(HashedString&& o) noexcept : mStrHash(std::exchange(o.mStrHash, 0)), mStr(std::move(o.mStr)) {}

    constexpr HashedString& operator=(const HashedString& o)
    {
        if (this != &o)
        {
            this->mStrHash = o.mStrHash;
            this->mStr = o.mStr;
        }
        return *this;
    }

    constexpr HashedString& operator=(HashedString&& o) noexcept
    {
        if (this != &o)
        {
            this->mStrHash = std::exchange(o.mStrHash, 0);
            this->mStr = std::move(o.mStr);
        }
        return *this;
    }

    constexpr HashedString(std::string str) : HashedString(computeHash(str), std::move(str)) {}
    constexpr HashedString(const HashType64 hash, std::string str) : mStrHash(hash), mStr(std::move(str)) {}

    constexpr bool operator==(const HashedString& rhs) const {
        if (this->mStrHash != rhs.mStrHash) return false;
        if (this->mLastMatch == &rhs && rhs.mLastMatch == this) return true;
        if (this->mStr != rhs.mStr) return false;
        this->mLastMatch = &rhs;
        rhs.mLastMatch = this;
        return true;
    }

    constexpr bool operator<(const HashedString& o) const
    {
        if (this->mStrHash < o.mStrHash) return true;
        if (this->mStrHash == o.mStrHash) return this->mStr < o.mStr;
        return false;
    }

    constexpr operator string_span() const
    {
        return string_span(mStr);
    }

    constexpr HashType64 getHash() const
    {
        return mStrHash;
    }

    constexpr const std::string& getString() const
    {
        return mStr;
    }

    constexpr const char* c_str() const
    {
        return mStr.c_str();
    }

    constexpr bool isEmpty() const
    {
        return mStr.empty();
    }

    constexpr bool empty() const
    {
        return mStr.empty();
    }

    constexpr void clear()
    {
        this->mStrHash = 0;
        this->mStr.clear();
    }

    static constexpr HashType64 computeHash(const std::string_view str)
    {
        if (str.empty()) return 0;
        uint64_t hash = 0xCBF29CE484222325;
        for (const char c : str) {
            hash *= 0x100000001B3; // 64bit Prime Multiplier
            hash ^= static_cast<uint64_t>(c);
        }
        return hash;
    }
};

static_assert(HashedString{}.getHash() == 0);
static_assert(HashedString{"amethyst"}.getHash() == 0x8846F44C0E605820);

constexpr inline HashedString HashedString::EMPTY{};

template <>
struct std::hash<HashedString> {
    std::size_t operator()(const HashedString& key) const
    {
        return key.getHash();
    }
};

class StringKey : public HashedString {
protected:
    mutable const StringKey* mMatch = nullptr;

public:
    StringKey() = default;

    StringKey(HashedString&&);

    StringKey(StringKey&& rha) noexcept : HashedString(rha),
                                          mMatch(nullptr) {}

    StringKey(const HashedString& key) : HashedString(key),
                                         mMatch(nullptr) {}

    StringKey(const StringKey& key) : HashedString(key),
                                      mMatch(nullptr) {}

    StringKey(const std::string& key) : HashedString(key),
                                        mMatch(nullptr) {}

    StringKey& operator=(const HashedString&);

    StringKey& operator=(const StringKey& key)
    {
        HashedString::operator=(key);
        mMatch = nullptr;
        return *this;
    }

    bool operator==(const StringKey&) const;
};

template <>
struct std::hash<StringKey> {
    std::size_t operator()(const StringKey& key) const
    {
        return key.getHash();
    }
};