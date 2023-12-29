#include "minecraft/src/common/world/actor/Actor.h"

template <typename T>
const T* Actor::tryGetComponent() const
{
    const auto& registry = mEntityContext.getRegistry();
    return registry.try_get<T>(mEntityContext.mEntity);
}

template const ActorHeadRotationComponent* Actor::tryGetComponent<ActorHeadRotationComponent>() const;
template const ActorRotationComponent* Actor::tryGetComponent<ActorRotationComponent>() const;