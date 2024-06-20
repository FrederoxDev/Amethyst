#pragma once

namespace mce {
    class Math {
    public:
        template <typename T>
        static constexpr size_t hash_accumulate(size_t hash, const T& toHash)
        {
            return ((hash >> 2) + (hash << 6) + std::hash<T>{}(toHash) + 0x9E3779B9u) ^ hash;
        }

        static constexpr size_t hash_accumulate_hashed(size_t hash, size_t other)
        {
            return ((hash >> 2) + (hash << 6) + other + 0x9E3779B9u) ^ hash;
        }
    };
};