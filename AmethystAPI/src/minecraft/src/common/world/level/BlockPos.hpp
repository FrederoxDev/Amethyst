#pragma once

class BlockPos {
public:
    int x;
    int y;
    int z;

    BlockPos(int x, int y, int z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    BlockPos below() const
    {
        return {this->x, this->y - 1, this->z};
    }
};