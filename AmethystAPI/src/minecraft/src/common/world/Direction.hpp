#pragma once

class Direction {
public:
    enum Type : char {
        SOUTH,
        WEST,
        NORTH,
        EAST,
        UNDEFINED = -1
    };
};