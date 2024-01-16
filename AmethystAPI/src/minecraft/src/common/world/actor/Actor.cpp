#include "common/world/actor/Actor.h"

Vec3* Actor::getPosition()
{
    return &mStateVectorComponent->mPos;
}

template <typename T>
const T* Actor::tryGetComponent() const
{
    const auto& registry = mEntityContext.getRegistry();
    return registry.try_get<T>(mEntityContext.mEntity);
}

template const ActorHeadRotationComponent* Actor::tryGetComponent<ActorHeadRotationComponent>() const;
template const ActorRotationComponent* Actor::tryGetComponent<ActorRotationComponent>() const;
template const StateVectorComponent* Actor::tryGetComponent<StateVectorComponent>() const;

template <typename T>
T* Actor::tryGetComponent()
{
    auto& registry = mEntityContext.getRegistry();
    return registry.try_get<T>(mEntityContext.mEntity);
}

template ActorHeadRotationComponent* Actor::tryGetComponent<ActorHeadRotationComponent>();
template ActorRotationComponent* Actor::tryGetComponent<ActorRotationComponent>();
template StateVectorComponent* Actor::tryGetComponent<StateVectorComponent>();