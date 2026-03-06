// #pragma once
// #include <vector>
// #include <map>
// #include <memory>
// #include <amethyst/runtime/input/InputAction.hpp>

// class VanillaClientInputMappingFactory;
// class KeyboardInputMapping;
// class MouseInputMapping;
// class AmethystContext;
// class InputAction;
// class InputHandler;
// class ButtonEventData;
// class IClientInstance;

// namespace Amethyst {
// class InputManager {
// public:
//     InputManager(AmethystContext* amethyst);
//     InputManager(const InputManager&) = delete;
//     InputManager(InputManager&&) = delete;
//     InputManager& operator=(const InputManager&) = delete;
//     InputManager& operator=(InputManager&&) = delete;
//     ~InputManager();

//     InputAction& RegisterNewInput(const std::string& actionName, std::vector<int> defaultKeys, bool allowRemapping = true, KeybindContext context = KeybindContext::Gameplay);
//     InputAction& GetVanillaInput(const std::string& actionName);

// private:
//     std::unordered_map<uint32_t, std::unique_ptr<InputAction>> mActions;
//     std::vector<InputActionOptions> mCustomInputs;

// private:
//     AmethystContext* mAmethyst;
//     friend class AmethystRuntime;

// public:
//     InputPassthrough _handleButtonEvent(InputHandler* handler, const ButtonEventData& button, FocusImpact focus, IClientInstance& client, int controllerId) const;
//     void _registerKeyboardInputs(VanillaClientInputMappingFactory* inputs, KeyboardInputMapping* keyboard, MouseInputMapping* mouse, Amethyst::KeybindContext context);
// };

// }