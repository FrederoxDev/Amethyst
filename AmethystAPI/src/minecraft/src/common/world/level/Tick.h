#pragma once
#include <cstdint>

struct Tick {
public:
    uint64_t tickID;

    Tick() {
        this->tickID = 0;
    }
};