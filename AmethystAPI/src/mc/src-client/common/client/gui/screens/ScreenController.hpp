/// @symbolgeneration
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
	/// @signature {48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 54 41 55 41 56 41 57 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 0F 10 52}
	MC ui::ViewRequest _handleButtonEvent(ScreenEvent& event);
};
