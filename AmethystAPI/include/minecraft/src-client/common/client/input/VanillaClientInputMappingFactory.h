#pragma once
#include "common/client/input/InputHandler.h"
#include "common/client/input/ClientInputMappingFactory.h"
#include <string>

class KeyboardInputMapping;
class MouseInputMapping;

class Remapping {
public:
    // From china 1.16.201
    enum ActionEnum : int32_t {
        Attack = 0x0000,
        PickItem = 0x0001,
        Use = 0x0002,
        Drop = 0x0003,
        Hotbar1 = 0x0004,
        Hotbar2 = 0x0005,
        Hotbar3 = 0x0006,
        Hotbar4 = 0x0007,
        Hotbar5 = 0x0008,
        Hotbar6 = 0x0009,
        Hotbar7 = 0x000a,
        Hotbar8 = 0x000b,
        Hotbar9 = 0x000c,
        Inventory = 0x000d,
        TogglePerspective = 0x000e,
        LookUpSlight = 0x000f,
        LookDownSlight = 0x0010,
        LookUpRight = 0x0011,
        LookUp = 0x0012,
        LookUpLeft = 0x0013,
        LookRight = 0x0014,
        LookCenter = 0x0015,
        LookLeft = 0x0016,
        LookDownRight = 0x0017,
        LookDown = 0x0018,
        LookDownLeft = 0x0019,
        LookUpSmooth = 0x001a,
        LookDownSmooth = 0x001b,
        LookLeftSmooth = 0x001c,
        LookRightSmooth = 0x001d,
        Jump = 0x001e,
        Sneak = 0x001f,
        Sprint = 0x0020,
        Left = 0x0021,
        Right = 0x0022,
        Back = 0x0023,
        Forward = 0x0024,
        Chat = 0x0025,
        Crafting = 0x0026,
        CycleItemLeft = 0x0027,
        CycleItemRight = 0x0028,
        Pause = 0x0029,
        FlyUpSlow = 0x002a,
        FlyDownSlow = 0x002b,
        MobEffects = 0x002c,
        ToastInteract = 0x002d,
        Command = 0x002e,
        MenuTabLeft = 0x002f,
        MenuTabRight = 0x0030,
        CodeBuilder = 0x0031,
        ImmersiveReader = 0x0032,
        Emote = 0x0033,
        MobEffectsAndToastInteract = 0x0034,
        COUNT = 0x0035,
    };
};

class VanillaClientInputMappingFactory : public ClientInputMappingFactory {
public:
    void createKeyboardAndMouseBinding(KeyboardInputMapping* keyboard, MouseInputMapping* mouse, const std::string* buttonName, const std::string* keyName, FocusImpact impact = FocusImpact::Neutral);

//hooks:
    // 40 55 53 56 57 41 56 48 8B EC 48 83 EC ? 45 0F B6 F1
    typedef void(__thiscall* __addFullKeyboardGamePlayControls)(VanillaClientInputMappingFactory*, KeyboardInputMapping*, MouseInputMapping*);
};