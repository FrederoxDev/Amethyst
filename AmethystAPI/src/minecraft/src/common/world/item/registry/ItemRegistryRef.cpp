#include "minecraft/src/common/world/item/registry/ItemRegistryRef.hpp"
#include "amethyst/Memory.hpp"

std::shared_ptr<ItemRegistry>** ItemRegistryRef::_lockRegistry(std::shared_ptr<ItemRegistry>** result) const
{
    using function = std::shared_ptr<ItemRegistry>**(__thiscall*)(const ItemRegistryRef*, std::shared_ptr<ItemRegistry>**);

    static auto func = reinterpret_cast<function>(
            SigScan("48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 48 8B DA 4C 8B C1")
    );

    return func(this, result);
}
