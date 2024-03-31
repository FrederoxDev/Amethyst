#include "UIComponent.h"
#include <memory>

class ToggleComponent : public UIComponent {
    std::weak_ptr<UIControl> mCheckedStateControl;
    std::weak_ptr<UIControl> mUncheckedStateControl;
    std::weak_ptr<UIControl> mCheckedHoverStateControl;
    std::weak_ptr<UIControl> mUncheckedHoverStateControl;
    std::weak_ptr<UIControl> mCheckedLockedStateControl;
    std::weak_ptr<UIControl> mCheckedLockedHoverStateControl;
    std::weak_ptr<UIControl> mUncheckedLockedStateControl;
    std::weak_ptr<UIControl> mUncheckedLockedHoverStateControl;
    bool mChecked;
    bool mHover;
    bool mRadioToggleGroup;
    bool mDefaultState;
};