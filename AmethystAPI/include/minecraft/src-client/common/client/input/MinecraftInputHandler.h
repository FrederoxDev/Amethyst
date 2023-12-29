#pragma once

class MinecraftInputHandler {
public:
    // 48 89 5C 24 ? 55 56 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B F1 48 8D 05
    typedef void*(__thiscall* ___registerInputHandlers)(MinecraftInputHandler*);
};