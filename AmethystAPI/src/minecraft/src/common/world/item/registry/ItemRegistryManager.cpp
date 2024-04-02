#include "minecraft/src/common/world/item/registry/ItemRegistryManager.hpp"

ItemRegistryRef ItemRegistryManager::getItemRegistry() {
    using function = ItemRegistryRef(*)();
    //                                                     48 8B 19 48 8B F9 48 85 DB 0F 85 ? ? ? ? E8 ? ? ? ? 48 8B C8 8D 53 ? 48 8B 00 48 8B 40 ? FF 15 ? ? ? ? 48 8B D8 48 85 C0 75 ? 48 8D 05 ? ? ? ? 48 C7 44 24 ? ? ? ? ? 4C 8D 0D ? ? ? ? 48 89 44 24 ? 44 8D 43 ? 48 8D 15 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 84 C0 74 ? C7 04 25 ? ? ? ? ? ? ? ? 48 8B 4F ? 48 89 5C 24 ? 48 85 C9 75 ? FF 15 ? ? ? ? CC 48 8B 11 48 8B 42 ? 48 8D 54 24 ? FF 15 ? ? ? ? 48 89 1F 48 8B C3 48 8B 4C 24 ? 48 33 CC E8 ? ? ? ? 48 8B 5C 24 ? 48 83 C4 ? 5F C3 CC 40 55
    static auto func = reinterpret_cast<function>(SigScan("40 53 48 83 EC ? 48 83 3D ? ? ? ? ? 48 8B D9 74"));
    return func();
}