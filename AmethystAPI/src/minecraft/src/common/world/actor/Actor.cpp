#include <amethyst/Memory.hpp>
#include "minecraft/src/common/world/actor/Actor.hpp"
#include "minecraft/src/common/world/level/dimension/Dimension.hpp"
#include "minecraft/src/common/world/entity/components/ActorHeadRotationComponent.hpp"
#include "minecraft/src/common/world/entity/components/ActorRotationComponent.hpp"
#include "minecraft/src/common/world/entity/components/StateVectorComponent.hpp"

Vec3* Actor::getPosition() const
{
    return &mBuiltInComponents.mStateVectorComponent->mPos;
}

Vec2* Actor::getHeadRot() const
{
    return &mBuiltInComponents.mActorRotationComponent->mHeadRot;
}

void Actor::moveTo(const Vec3& a1, const Vec2& a2)
{
    using function = decltype(&Actor::moveTo);
    static auto func = std::bit_cast<function>(SigScan("48 89 74 24 ? 48 89 7C 24 ? 41 56 48 83 EC ? 4C 8B B1 ? ? ? ? 48 8B FA"));
    return (this->*func)(a1, a2);
}

const Dimension& Actor::getDimensionConst() const
{
    return *mDimension.lock();
}

const BlockSource& Actor::getDimensionBlockSourceConst() const
{
    return *getDimensionConst().mBlockSource.get();
}

bool Actor::hasDimension() const
{
    return mDimension.lock() != nullptr;
}

void Actor::setDimension(WeakRef<Dimension> dimension)
{
    using function = decltype(&Actor::setDimension);
    static auto func = std::bit_cast<function>(SigScan("48 89 5C 24 ? 55 56 57 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 48 8B FA 48 8B E9 48 89 54 24 ? 0F 57 C9"));
    return (this->*func)(dimension);
}

int Actor::load(const CompoundTag& actorData, DefaultDataLoadHelper& dataLoadHelper)
{
    using function = decltype(&Actor::load);
    static auto func = std::bit_cast<function>(this->vtable[88]);
    return (this->*func)(actorData, dataLoadHelper);
}

void Actor::reload()
{
    using function = decltype(&Actor::reload);
    static auto func = std::bit_cast<function>(SigScan("48 89 5C 24 ? 48 89 74 24 ? 55 57 41 54 41 56 41 57 48 8B EC 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 48 8B F1 45 33 E4"));
    return (this->*func)();
}
