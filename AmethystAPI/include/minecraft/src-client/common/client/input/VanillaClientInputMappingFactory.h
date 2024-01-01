#pragma once

class KeyboardInputMapping;
class MouseInputMapping;

class VanillaClientInputMappingFactory {
public:
    // 48 89 5C 24 ? 55 56 57 48 8B EC 48 83 EC ? 49 8B F0 48 8B DA 48 8B F9 E8
    typedef void*(__thiscall* __createBaseNormalGamePlayKeyboardAndMouseMapping)(VanillaClientInputMappingFactory* self, KeyboardInputMapping* normalGamePlayKeyboardMapping, MouseInputMapping* normalGamePlayMouseMapping);

    // 40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 49 8B D9 4D 8B F8 4C 8B F2
    // void* _bindActionToKeyboardAndMouseInput(void*, void*, void*, void*, void*, ...);
    // void* _bindActionToKeyboardAndMouseInput(void*, void*, void*, void*, void*, char);
};