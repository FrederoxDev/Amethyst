#pragma once
#include "minecraft/src-deps/input/InputMappingFactory.h"
#include <unordered_map>
#include <string>
#include "minecraft/src-deps/input/InputMapping.h"

class InputMapping {
public:
    KeyboardInputMapping keyboardMapping;
};

class ClientInputMappingFactory : public InputMappingFactory {
public:
    std::unordered_map<std::string, InputMapping> mActiveInputMappings;
};