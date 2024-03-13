#include "HookManager.h"

/*
Disables any hooks and un-caches any stored addresses
*/
void HookManager::Shutdown()
{
    for (auto it = mHooks.rbegin(); it != mHooks.rend(); ++it) {
        auto* hook = *it;
        *hook = {};
    }

    mHooks.clear();
    mFuncHashToOriginalAddress.clear();
}