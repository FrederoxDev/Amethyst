#ifdef CLIENT
#include "hooks/client/Rendering.hpp"

#include <amethyst/runtime/ModContext.hpp>
#include <amethyst/runtime/utility/InlineHook.hpp>
#include <amethyst/runtime/events/RenderingEvents.hpp>

#include <common/client/renderer/game/LevelRenderer.hpp>

namespace Amethyst::ClientHooks::RenderingHooks {
	// Amethyst::InlineHook<decltype(&LevelRenderer::renderLevel)> _LevelRenderer_renderLevel;
	// void LevelRenderer_renderLevel(LevelRenderer* self, ScreenContext& screenContext, FrameRenderObject& frameRenderObj) {
	// 	Amethyst::EventBus& bus = Amethyst::GetEventBus();
	// 	BeforeRenderLevelEvent beforeEvent(*self, screenContext, frameRenderObj);
	// 	bus.Invoke(beforeEvent);
	// 	_LevelRenderer_renderLevel(self, screenContext, frameRenderObj);
	// 	AfterRenderLevelEvent afterEvent(*self, screenContext, frameRenderObj);
	// 	bus.Invoke(afterEvent);
	// }

	void Initialize() {
		auto& hooks = Amethyst::GetHookManager();
		// HOOK(LevelRenderer, renderLevel);
	}
}
#endif
