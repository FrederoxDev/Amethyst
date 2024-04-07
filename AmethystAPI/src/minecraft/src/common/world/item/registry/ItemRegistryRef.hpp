#pragma once
#include <memory>
class ItemRegistry;

class ItemRegistryRef {
public:
    std::weak_ptr<ItemRegistry> mItemRegistry;

    // 1.20.51.1 - 48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 48 8B DA 4C 8B C1
    std::shared_ptr<ItemRegistry>** _lockRegistry(std::shared_ptr<ItemRegistry>** result) const;
};
