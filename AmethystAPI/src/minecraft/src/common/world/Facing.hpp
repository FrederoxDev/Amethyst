#pragma once

class Facing {
public:
    enum class Name : unsigned char {
        DOWN,
        UP,
        NORTH,
        SOUTH,
        WEST,
        EAST
    };

    static Facing::Name getOpposite(Facing::Name face);
    static Facing::Name getClockWise(Facing::Name face);
    static Facing::Name getCounterClockWise(Facing::Name face);
    static float getYAngle(Facing::Name face);
};

typedef Facing::Name FacingID;