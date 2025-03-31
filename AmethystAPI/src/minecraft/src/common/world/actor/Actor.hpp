#pragma once
#include <gsl/gsl>
#include "minecraft/src/common/world/entity/EntityContext.hpp"
#include <minecraft/src/common/gamerefs/WeakRef.hpp>

class Vec2;
class Vec3;
class Dimension;
class AABBShapeComponent;
class ActorWalkAnimationComponent;
struct StateVectorComponent;
struct ActorRotationComponent;
class DefaultDataLoadHelper;
class CompoundTag;
class ILevel;

struct BuiltInActorComponents {
    gsl::not_null<StateVectorComponent*> mStateVectorComponent;
    gsl::not_null<AABBShapeComponent*> mAABBShapeComponent;
    gsl::not_null<ActorRotationComponent*> mActorRotationComponent;
    gsl::not_null<ActorWalkAnimationComponent*> mWalkAnimationComponent;
};

enum ActorInitializationMethod : __int8 {
    INVALID = 0x0,
    LOADED = 0x1,
    SPAWNED = 0x2,
    BORN = 0x3,
    TRANSFORMED = 0x4,
    UPDATED = 0x5,
    EVENT = 0x6,
    LEGACY = 0x7,
};

#pragma pack(push, 1)
class Actor {
public:
    /* this + 0   */ uintptr_t** vtable;
    /* this + 8   */ EntityContext mEntityContext;
    /* this + 32  */ ActorInitializationMethod mInitMethod;
    /* this + 33  */ std::byte padding33[576 - 33];
    /* this + 576 */ std::weak_ptr<Dimension> mDimension; // moved -16 in 1.21
    /* this + 592 */ ILevel* mLevel;
    /* this + 600 */ std::byte padding592[56];
    /* this + 656 */ BuiltInActorComponents mBuiltInComponents; // 1.21
    /* this + 688 */ std::byte padding688[536];

public:
    Vec3* getPosition() const;
    Vec2* getHeadRot() const;
    void moveTo(const Vec3&, const Vec2&);

    const Dimension& getDimensionConst() const;
    bool hasDimension() const;
    void setDimension(WeakRef<Dimension> dimension);

    // Generics
    template <typename T>
    const T* tryGetComponent() const
    {
        const auto& registry = mEntityContext.getRegistry();
        return registry.try_get<T>(mEntityContext.mEntity);
    }

    template <typename T>
    T* tryGetComponent()
    {
        auto& registry = mEntityContext.getRegistry();
        return registry.try_get<T>(mEntityContext.mEntity);
    }

    int load(const CompoundTag&, DefaultDataLoadHelper&);
    void reload();
};
#pragma pack(pop)   

static_assert(sizeof(Actor) == 1224);