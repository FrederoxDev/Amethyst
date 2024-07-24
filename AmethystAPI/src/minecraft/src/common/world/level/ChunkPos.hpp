#pragma once
#include <cstdint>
#include <fmt/core.h>

class ChunkPos {
public:
    union {
        struct {
        public:
            int32_t x;
            int32_t z;
        };

    public:
        int64_t packed;
    };

public:
    ChunkPos() {
        x = 0;
        z = 0;
    };

    ChunkPos(int32_t x, int32_t z) {
        this->x = x;
        this->z = z;
    }

    ChunkPos(int64_t packed) {
        this->packed = packed;
    }

    bool operator==(const ChunkPos& r) const {
        return this->packed == r.packed;
    }
};

namespace std {
template <>
struct hash<ChunkPos> {
    size_t operator()(const ChunkPos& pos) const;
};

inline size_t hash<ChunkPos>::operator()(const ChunkPos& pos) const
{
    return pos.packed;
}
} // namespace std

template <>
struct fmt::formatter<ChunkPos> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }

    template <typename FormatContext>
    auto format(const ChunkPos& pos, FormatContext& ctx)
    {
        return fmt::format_to(ctx.out(), "ChunkPos(x: {}, z: {})", pos.x, pos.z);
    }
};