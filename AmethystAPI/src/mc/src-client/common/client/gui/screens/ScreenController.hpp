/// @symbols
#pragma once
#include <amethyst/Imports.hpp>

class ScreenEvent;

namespace ui {
enum class ViewRequest : uint32_t {
	None = 0,
	Refresh = 1u << 0,
	PointerHeldEventsRequest = 1u << 1,
	PointerHeldEventsCancel = 1u << 2,
	DelayedFocusRefresh = 1u << 3,
	Exit = 1u << 4,
	ConsumeEvent = 1u << 5,
};
}

class ScreenController {
public:
	/// @address {0x483EC00}
	MC ui::ViewRequest _handleButtonEvent(ScreenEvent& event);
};
