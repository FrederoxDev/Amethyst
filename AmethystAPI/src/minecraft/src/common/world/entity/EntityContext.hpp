#pragma once
#include "minecraft/src/common/world/entity/EntityId.hpp"

class EntityRegistry;

class EntityContext {
public:
    EntityRegistry& mRegistry;
    entt::basic_registry<EntityId>& mEnttRegistry;
    EntityId mEntity;

    [[nodiscard]] inline entt::basic_registry<EntityId>& getRegistry()
    {
        return mEnttRegistry;
    }

    [[nodiscard]] inline entt::basic_registry<EntityId> const& getRegistry() const
    {
        return mEnttRegistry;
    }
};