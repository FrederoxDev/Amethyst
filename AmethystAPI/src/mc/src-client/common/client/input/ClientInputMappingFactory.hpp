/// @symbols
#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include "mc/src-deps/input/InputMappingFactory.hpp"
#include "mc/src-deps/input/InputMapping.hpp"

class RemappingLayout;

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

    /// @vidx { inherit, this }
    MC virtual ~ClientInputMappingFactory();
};

static_assert(sizeof(ClientInputMappingFactory) == 0x150);