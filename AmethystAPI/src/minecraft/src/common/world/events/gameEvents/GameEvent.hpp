#pragma once

namespace GameEventConfig {
    using GameEventCategoriesStorage = unsigned char;

    enum GameEventType : int {
        _Invalid,
        BlockActivate,
        BlockAttach,
        BlockChange,
        BlockClose,
        BlockDeactivate,
        BlockDestroy,
        BlockDetach,
        BlockOpen,
        BlockPlace,
        ContainerClose,
        ContainerOpen,
        DispenseFail,
        Drink,
        Eat,
        ElytraGlide,
        EntityDamage,
        EntityDie,
        EntityInteract,
        EntityMove,
        EntityPlace,
        EntityRoar,
        EntityShake,
        Equip,
        Explode,
        Flap,
        FluidPickup,
        FluidPlace,
        HitGround,
        ItemInteractFinish,
        ItemInteractStart,
        LightningStrike,
        NoteBlockPlay,
        PistonContract,
        PistonExtend,
        PrimeFuse,
        ProjectileLand,
        ProjectileShoot,
        SculkTouch,
        SculkSensorTendrilsClicking,
        Shear,
        Shriek,
        Splash,
        Swim,
        _Count
    };
}

class GameEvent {
public:
    const GameEventConfig::GameEventType mType;
    const GameEventConfig::GameEventCategoriesStorage mCategories;
};