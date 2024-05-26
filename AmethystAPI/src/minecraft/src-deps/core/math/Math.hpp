#pragma once

namespace mce {
    class Math {
    public:
        template <typename T>
        constexpr inline static size_t hash_accumulate(size_t hash, const T& toHash)
        {
            return ((hash >> 2) + (hash << 6) + std::hash<T>{}(toHash) + 0x9E3779B9u) ^ hash;
        }

        constexpr static size_t hash2(const auto& a, const auto& b)
        {
            size_t hash{};
            hash = hash_accumulate(0LL, a);
            hash = hash_accumulate(hash, b);
            return hash;
        }

        constexpr static size_t hash3(const auto& a, const auto& b, const auto& c)
        {
            size_t hash{};
            hash = hash_accumulate(0LL, a);
            hash = hash_accumulate(hash, b);
            hash = hash_accumulate(hash, c);
            return hash;
        }
    };
};