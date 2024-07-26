#pragma once
#include <minecraft/src-deps/core/utility/NonOwnerPointer.hpp>
#include <minecraft/src/common/gamerefs/StackRefResult.hpp>

class EntityRegistry;

class IEntityRegistryOwner : public Bedrock::EnableNonOwnerReferences {
protected:
    virtual ~IEntityRegistryOwner();
public:
    virtual StackRefResult<const EntityRegistry> getEntityRegistry() const;
    virtual StackRefResult<EntityRegistry> getEntityRegistry();
};