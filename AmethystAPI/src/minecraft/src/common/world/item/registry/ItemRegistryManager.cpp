#include "common/world/item/registry/ItemRegistryManager.h"

ItemRegistryRef ItemRegistryManager::getItemRegistry() {
    using function = ItemRegistryRef(*)();
    static auto func = reinterpret_cast<function>(SigScan("40 53 48 83 EC ? 48 83 3D ? ? ? ? ? 48 8B D9 74"));
    return func();
}