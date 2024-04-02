#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include "minecraft/src-deps/input/InputMappingFactory.hpp"
#include "minecraft/src-deps/input/InputMapping.hpp"
#include "minecraft/src-client/common/client/input/RemappingLayout.hpp"

class InputMapping {
public:
    KeyboardInputMapping keyboardMapping;
};

// Todo fill out this class if we want to support controller
class GamePadRemappingLayout {
    std::byte padding[0x58];
};

static_assert(sizeof(GamePadRemappingLayout) == 0x58);

class ClientInputMappingFactory : public InputMappingFactory {
public:
    std::unordered_map<std::string, InputMapping> mActiveInputMappings;
    std::unordered_map<std::string, InputMapping> mInputMappingTemplates;
    bool mInvertYAxis;
    bool mSwapGamepadButtonsXY;
    bool mSwapGamepadButtonsAB;
    float mSensitivity;
    GamePadRemappingLayout mGameControllerRemappingLayout;
    GamePadRemappingLayout mMotionControllerRemappingLayout;
    std::shared_ptr<RemappingLayout> mLayout;
};

static_assert(sizeof(ClientInputMappingFactory) == 0x150);