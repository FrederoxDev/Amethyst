// Yoink! https://github.com/LiteLDev/LeviLamina/blob/24546ef17d8049760bf7573b32ede05cb0958fe9/src/mc/entity/EntityIdTraits.h
#pragma once
#include <stdint.h>

class EntityId;

struct EntityIdTraits {
    using value_type = EntityId;

    using entity_type = uint64_t;
    using version_type = uint16_t;

    static constexpr entity_type entity_mask = 0x3FFFF;
    static constexpr entity_type version_mask = 0x3FFF;
};