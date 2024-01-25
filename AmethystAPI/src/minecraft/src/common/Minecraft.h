#pragma once

class Minecraft {
public:
    typedef bool (__thiscall* _update)(Minecraft*);
    bool update(Minecraft*);
};