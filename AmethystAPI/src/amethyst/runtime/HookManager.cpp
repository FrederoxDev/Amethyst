#include "HookManager.hpp"

#include <ranges>

/*
Disables any hooks and un-caches any stored addresses
*/
Amethyst::HookManager::~HookManager()
{
    for (auto hook : std::ranges::reverse_view(mHooks)) {
        *hook = {};
    }

    mHooks.clear();
    mFuncHashToOriginalAddress.clear();
}