#pragma once

#include <cstdint>

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
};