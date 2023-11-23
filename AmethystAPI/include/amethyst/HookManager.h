#pragma once
#include "MinHook.h"
#include "amethyst/Log.h"
#include <vector>

class HookManager {
public:
    HookManager();
    void CreateHook(uintptr_t original_address, void* detour, void* original);

private:
    std::vector<LPVOID> m_hooks;
};