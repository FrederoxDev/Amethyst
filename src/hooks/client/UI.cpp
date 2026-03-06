// #ifdef CLIENT
// #include "hooks/client/UI.hpp"

// #include <amethyst/runtime/ModContext.hpp>
// #include <amethyst/runtime/utility/InlineHook.hpp>
// #include <amethyst/runtime/events/RenderingEvents.hpp>
// #include <amethyst/runtime/events/UiEvents.hpp>

// #include <mc/src-client/common/client/gui/ScreenView.hpp>
// #include <mc/src-client/common/client/gui/screens/ScreenController.hpp>

// namespace Amethyst::ClientHooks::UIHooks {
// 	Amethyst::InlineHook<decltype(&ScreenView::setupAndRender)> _ScreenView_setupAndRender;
// 	void ScreenView_setupAndRender(ScreenView* self, MinecraftUIRenderContext& ctx) {
// 		auto& bus = Amethyst::GetEventBus();
// 		BeforeRenderUIEvent ev(*self, ctx);
// 		bus.Invoke(ev);
// 		_ScreenView_setupAndRender(self, ctx);
// 		AfterRenderUIEvent afterEv(*self, ctx);
// 		bus.Invoke(afterEv);
// 	}

// 	Amethyst::InlineHook<decltype(&ScreenController::_handleButtonEvent)> _ScreenController__handleButtonEvent;
// 	ui::ViewRequest ScreenController__handleButtonEvent(ScreenController* screen, ScreenEvent& event) {
// 		ui::ViewRequest result = _ScreenController__handleButtonEvent(screen, event);
// 		UIButtonHandleEvent ev(event);
// 		Amethyst::GetEventBus().Invoke(ev);
// 		return result;
// 	}

// 	void Initialize() {
// 		auto& hooks = Amethyst::GetHookManager();
// 		HOOK(ScreenView, setupAndRender);
// 		HOOK(ScreenController, _handleButtonEvent);
// 	}
// }
// #endif
