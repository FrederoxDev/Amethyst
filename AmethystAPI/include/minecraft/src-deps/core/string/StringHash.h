#pragma once

#include "core/headerIncludes/gsl_includes.h"

#include <string>

typedef uint64_t HashType64;

// FNV-1
template <std::size_t V>
HashType64 calculate_string_hash()
{
    return V;
}

template <std::size_t V, char C, char... Cs>
HashType64 calculate_string_hash()
{
    return calculate_string_hash<(V * 0x100000001B3) ^ C, Cs...>();
}

template <std::size_t... N, typename Literal>
HashType64 templatize_string_to_chars(std::index_sequence<N...>, Literal)
{
    return calculate_string_hash<0xCBF29CE484222325, Literal::get(N)...>();
}

#define STRING_LITERAL_HASH(s)                                            \
    templatize_string_to_chars(std::make_index_sequence<sizeof(s) - 1>(), \
                               []() {                                     \
                                   struct Literal {                       \
                                       static constexpr char get(int i)   \
                                       {                                  \
                                           return s[i];                   \
                                       }                                  \
                                   };                                     \
                                   return Literal{};                      \
                               }())

namespace RunTime {
inline uint64_t hash64(const char* str)
{
    uint64_t ret = 0xCBF29CE484222325;
    if (str) {
        while (*str) {
            ret = (ret * 0x100000001B3) ^ *str++;
        }
    }
    return ret;
}
} // namespace RunTime

class HashedString {
public:
    static HashedString defaultErrorValue;

private:
    HashType64 mStrHash = 0;
    std::string mStr;

    template <typename T>
    struct StringHasher {
        static HashType64 hash(T str) { return 0; }
    };

    template <typename T>
    static HashType64 hash(const T& str)
    {
        return HashedString::StringHasher<T>::hash(str);
    }

public:
    HashedString() = default;
    HashedString(std::nullptr_t);
    HashedString(const HashedString&);
    HashedString(HashedString&&) noexcept;
    HashedString(HashType64 hash, const char* str);
    HashedString(const char* str);
    HashedString(const std::string& str);
    HashedString(HashType64 hash, std::string str);
    HashedString& operator=(const HashedString&);
    bool operator==(const HashedString&) const;
    bool operator!=(const HashedString&) const;
    bool operator<(const HashedString&) const;

    operator string_span() const
    {
        return string_span(mStr);
    }

    HashType64 getHash() const;
    const std::string& getString() const;
    const char* c_str() const;
    bool isEmpty() const;
    bool empty() const;
    void clear();
    static const HashedString& getEmptyString();
    static HashType64 computeHash(const char* str);
    static HashType64 computeHash(const std::string& str);

private:
    template <>
    struct StringHasher<const char*> {
    public:
        static HashType64 hash(const char* str)
        {
            // never compiled without const char*
            return RunTime::hash64(str);
        }
    };
};

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