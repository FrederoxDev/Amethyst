#pragma once
#include <string>

namespace Amethyst {
    class InputAction {
    public:
        std::string mInputName;
        int mDefaultButton;
        bool mAllowRemapping;

    public:
        InputAction(const std::string& inputName, int defaultButton, bool allowRemapping) {
            mInputName = inputName;
            mDefaultButton = defaultButton;
            mAllowRemapping = allowRemapping;
        }
    };
}; // namespace Amethyst