#pragma once
#include "entt/entt.hpp"
#include <cstdint>

class EntityId;

struct EntityIdTraits {
    using value_type = EntityId;

    using entity_type = uint32_t;
    using version_type = uint16_t;

    static constexpr entity_type entity_mask = 0x3FFFF;
    static constexpr version_type version_mask = 0x3FFF;
};

// Specialize entt::storage_type by removing sigh_mixin
template <typename Type>
struct entt::storage_type<Type, EntityId> {
    using type = basic_storage<Type, EntityId>;
};