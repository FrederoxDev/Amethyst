#pragma once
#include <string> 
#include <vector>
#include <functional>
#include <Input/Enums/FocusImpact.hpp>
#include <Input/Enums/ButtonState.hpp>

class InputHandler;
class ClientInstance;

namespace Amethyst {

/*
 * Defines the context in which a keybind is active.
 * E.g. `exampleKeybindContext::Gameplay | KeybindContext::Screen`
 */
enum class KeybindContext {
    None = 0,
    Gameplay = 1 << 0,
    Screen = 1 << 1,
};

inline KeybindContext operator|(KeybindContext lhs, KeybindContext rhs)
{
    using T = std::underlying_type_t<KeybindContext>;
    return static_cast<KeybindContext>(
        static_cast<T>(lhs) | static_cast<T>(rhs));
}

inline KeybindContext operator&(KeybindContext lhs, KeybindContext rhs)
{
    using T = std::underlying_type_t<KeybindContext>;
    return static_cast<KeybindContext>(
        static_cast<T>(lhs) & static_cast<T>(rhs));
}

class InputActionOptions {
public:
    std::string mActionName;
    std::vector<int> mDefaultKeys;
    bool mAllowRemapping;
    KeybindContext mContexts;

    InputActionOptions(
        const std::string& actionName, 
        std::vector<int> defaultKeys,
        bool allowRemapping = true,
        KeybindContext contexts = KeybindContext::Gameplay
    )
        : mActionName(actionName),
          mDefaultKeys(std::move(defaultKeys)),
          mAllowRemapping(allowRemapping),
          mContexts(contexts) {}
};

enum class InputPassthrough {
    // Allows both mod and vanilla handling of the input event
    Passthrough,

    // Prevents further processing of the input event
    Consume,

    // Allows mod handling but prevents vanilla handling
    ModOnly,
};

class InputAction {
private:
    uint32_t mNameHash;
    std::vector<std::function<InputPassthrough(FocusImpact, ClientInstance&)>> mButtonDownHandlers;
    std::vector<std::function<InputPassthrough(FocusImpact, ClientInstance&)>> mButtonUpHandlers;

public:
    InputAction(const std::string& actionName);
    uint32_t getNameHash() const { return mNameHash; }
    void addButtonDownHandler(std::function<InputPassthrough(FocusImpact, ClientInstance&)> handler);
    void addButtonUpHandler(std::function<InputPassthrough(FocusImpact, ClientInstance&)> handler);

private:
    InputPassthrough _onButtonStateChange(ButtonState state, FocusImpact focus, ClientInstance& client) const;
    friend class InputManager;
};

}; // namespace Amethyst