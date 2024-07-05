#pragma once

class BaseGameVersion;
class Experiments;
class ItemRegistryRef;

class VanillaItems {
public:
    // 1.21.0.3 - 40 55 53 56 57 41 54 41 56 41 57 48 8D AC 24 ? ? ? ? B8 ? ? ? ? E8 ? ? ? ? 48 2B E0 0F 29 B4 24
    static void registerItems(void* a1, const ItemRegistryRef itemRegistry, const BaseGameVersion* baseGameVersion, const Experiments* experiments);
};