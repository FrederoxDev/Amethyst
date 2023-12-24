// Yoink! https://github.com/LiteLDev/LeviLamina/blob/24546ef17d8049760bf7573b32ede05cb0958fe9/src/mc/entity/EntityId.h
#pragma once
#include <concepts>
#include <stdint.h>
#include "minecraft/src/common/world/entity/EntityIdTraits.h"
#include "entt/entt.hpp"

template <>
class entt::entt_traits<EntityId> : public entt::basic_entt_traits<EntityIdTraits> {
public:
    static constexpr entity_type page_size = 2048;
};

class EntityId : public entt::entt_traits<EntityId> {
public:
    entity_type mRawId{};

    template <std::integral T>
        requires(!std::is_same_v<std::remove_cvref_t<T>, bool>)
    [[nodiscard]] constexpr EntityId(T rawId) : mRawId(static_cast<entity_type>(rawId)) {} // NOLINT

    [[nodiscard]] constexpr bool isNull() const { return *this == entt::null; }

    template <std::integral T>
        requires(!std::is_same_v<std::remove_cvref_t<T>, bool>)
    [[nodiscard]] constexpr operator T() const {
        return static_cast<T>(mRawId);
    }
};