#pragma once
#include "minecraft/src/common/world/entity/EntityId.h"

class EntityRegistry;

class EntityContext {
public:
    EntityRegistry& mRegistry;
    entt::basic_registry<EntityId>& mEnttRegistry;
    EntityId mEntity;
};