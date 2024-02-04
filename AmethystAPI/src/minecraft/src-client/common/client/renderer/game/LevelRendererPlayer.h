#pragma once
#include "amethyst/Memory.h"

class LevelRendererPlayer {
public:
    //48 8B C4 48 89 58 ? 48 89 70 ? 57 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 44 0F 29 40 ? 44 0F 29 48 ? 48 8B 05
    virtual float getFov(float, bool);

public:
    typedef float(__thiscall* _getFov)(LevelRendererPlayer*, float, bool);
};