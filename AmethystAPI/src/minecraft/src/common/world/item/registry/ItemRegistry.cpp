#include "minecraft/src/common/world/item/registry/ItemRegistry.hpp"

void ItemRegistry::registerItem(SharedPtr<Item> item)
{
	using function = decltype(&ItemRegistry::registerItem);

    // 1.20.71.1
    static auto func = std::bit_cast<function>(
            SigScan("48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 8B EA 4C 8B F1 48 89 4C 24 ? 48 89 55")
    );

    (this->*func)(item);
}