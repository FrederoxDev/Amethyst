#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include "minecraft/src-deps/input/InputMappingFactory.h"
#include "minecraft/src-deps/input/InputMapping.h"
#include "minecraft/src-client/common/client/input/RemappingLayout.h"

class InputMapping {
public:
    KeyboardInputMapping keyboardMapping;
};

class ClientInputMappingFactory : public InputMappingFactory {
public:
    std::unordered_map<std::string, InputMapping> mActiveInputMappings;
    bool padding[248];
    std::shared_ptr<RemappingLayout> mLayout;
};