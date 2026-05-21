// #ifdef CLIENT
// #include "CustomUIRendererRegistry.hpp"
// #include <client/gui/controls/UIControlFactory.hpp>
// #include <client/gui/controls/CustomRenderComponent.hpp>
// #include <client/gui/UIResolvedDef.hpp>
// #include <client/gui/controls/UIControl.hpp>
// #include <client/gui/controls/renderers/MinecraftUICustomRenderer.hpp>
// #include "game/client/CustomUIRendererRegistry.hpp"

// Amethyst::InlineHook<decltype(&UIControlFactory::_populateCustomRenderComponent)> _UIControlFactory__populateCustomRenderComponent;

// void UIControlFactory__populateCustomRenderComponent(UIControlFactory* factory, const UIResolvedDef& resolved, UIControl& control) {
// 	auto* modComponentsFactory = (CustomUIRendererRegistry*)Amethyst::GetClientCtx().mCustomUIRendererRegistry.get();

// 	if (!modComponentsFactory) {
// 		_UIControlFactory__populateCustomRenderComponent(factory, resolved, control);
// 		return;
// 	}

// 	std::string rendererType = resolved.getAsString("renderer");

// 	auto customComponent = modComponentsFactory->tryCreateRenderer(rendererType);
// 	if (customComponent) {
// 		control.setComponent<CustomRenderComponent>(
// 			std::make_unique<CustomRenderComponent>(control)
// 		);

// 		CustomRenderComponent* component = control.getComponent<CustomRenderComponent>();
// 		component->setRenderer(customComponent);
// 		return;
// 	}

// 	_UIControlFactory__populateCustomRenderComponent(factory, resolved, control);
// }

// void CustomUIRendererRegistry::AddEventListeners() {
// 	auto& hooks = Amethyst::GetHookManager();
// 	HOOK(UIControlFactory, _populateCustomRenderComponent);
// }
// #endif