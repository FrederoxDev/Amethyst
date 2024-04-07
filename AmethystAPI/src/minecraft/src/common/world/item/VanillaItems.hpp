#pragma once
#include "minecraft/src/common/world/item/registry/ItemRegistryRef.hpp"

class BaseGameVersion;
class Experiments;

class VanillaItems {
public:
    // 1.20.51.1 - 40 55 53 56 57 41 54 41 56 41 57 48 8D AC 24 ? ? ? ? B8 ? ? ? ? E8 ? ? ? ? 48 2B E0 0F 29 B4 24
    static void registerItems(const ItemRegistryRef itemRegistry, const BaseGameVersion* baseGameVersion, const Experiments* experiments, bool enableExperimentalGameplay);
};