#pragma once

#include "minecraft/client/input/InputHandler.h"

#include <cstdint>
#include <memory>

class MinecraftInputHandler {
public:
    uintptr_t** vtable;
    bool padding[24];
    std::unique_ptr<InputHandler> mInputHandler;

//hooks:
    // 48 89 5C 24 ? 55 56 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B F1 48 8D 05
    typedef void*(__thiscall* __registerInputHandlers)(MinecraftInputHandler*);
};