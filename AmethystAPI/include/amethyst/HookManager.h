#pragma once
#include "MinHook.h"
#include "amethyst/Log.h"
#include "amethyst/Memory.h"
#include <vector>

class HookManager {
public:
    void CreateHook(uintptr_t targetAddress, void* detour, void** original);
    void Shutdown();

private:
    std::vector<LPVOID> m_hooks;
};