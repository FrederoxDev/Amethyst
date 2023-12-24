#pragma once
#include "minecraft/src/common/world/entity/EntityId.h"
#include "minecraft/src/common/wrapper/optional_ref.h"

class EntityRegistry;

class EntityContext {
public:
    EntityRegistry& mRegistry;
    entt::basic_registry<EntityId>& mEnttRegistry;
    EntityId mEntity;

    [[nodiscard]] inline entt::basic_registry<EntityId>& getRegistry() { 
        return mEnttRegistry; 
    }

    [[nodiscard]] inline entt::basic_registry<EntityId> const& getRegistry() const { 
        return mEnttRegistry; 
    }

    template <class T>
    [[nodiscard]] inline optional_ref<T const> tryGetComponent() const {
        return getRegistry().try_get<T>(mEntity);
    }
};