#include "minecraft/src/common/world/item/registry/ItemRegistry.h"

void ItemRegistry::registerItem(SharedPtr<Item> item)
{
	using function = decltype(&ItemRegistry::registerItem);

    static auto func = std::bit_cast<function>(
            SigScan("48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 48 8B FA 4C 8B E9 48 89 55 ? 33 DB")
    );

    (this->*func)(item);
}