/// @symbols
#pragma once
#include <amethyst/Imports.hpp>
#include <string_view>
#include <string>

namespace Json { class Value; }
class UIControl;
class UIResolvedDef;
class UIControlFactoryContext;
class ControlScreenAction;
class CustomRenderComponent;

namespace ui {
enum class ChildInsertPosition : int32_t {
	Front = 0,
	Back = 1,
};
}

class UIControlFactory {
public:
//begin members:
	// UIControlFactory(gsl::not_null<Bedrock::NonOwnerPointer<const IUIDefRepository>>, const Json::Value&, const UISoundPlayer&, FontHandle, FontHandle, FontHandle, FontHandle, bool);

	// ~UIControlFactory();

	UnknownReturn getInitSelectedControl() const;

	UnknownReturn getUIDef(std::string_view unk0);

	UnknownReturn setGlobalVars(const Json::Value& unk0);

	UnknownReturn addAnimRefToControl(UIControl& unk0, std::string_view unk1);

	UnknownReturn _addAnimToComponent(std::string_view unk0, UIControl& unk1);

	UnknownReturn _addAnimToComponent(std::string_view unk0, UIResolvedDef& unk1, UIControl& unk2);

	UnknownReturn _createButton(UIControl& unk0, const UIResolvedDef& unk1);

	UnknownReturn _createCollectionPanel(UIControl& unk0, const UIResolvedDef& unk1);

	UnknownReturn _createControlTree(const UIControlFactoryContext& unk0, std::string_view unk1, ControlScreenAction& unk2, UIControl* unk3, ui::ChildInsertPosition unk4, Json::Value* unk5, bool unk6);

	UnknownReturn _createControlTree(const UIControlFactoryContext& unk0, const UIControl& unk1, UIControl* unk2, ui::ChildInsertPosition unk3);

	UnknownReturn _createControlTreeFromResolvedDef(const UIControlFactoryContext& unk0, const UIResolvedDef& unk1, UIControl* unk2, ControlScreenAction& unk3, ui::ChildInsertPosition unk4, bool unk5);

	UnknownReturn _createControlTreeRootOnly(const UIControlFactoryContext& unk0, std::string_view unk1, ControlScreenAction& unk2);

	UnknownReturn _createCustom(UIControl& unk0, const UIResolvedDef& unk1);

	UnknownReturn _createDropdown(UIControl& unk0, const UIResolvedDef& unk1);

	UnknownReturn _createEditBox(UIControl& unk0, const UIResolvedDef& unk1);

	UnknownReturn _createFactory(UIControl& unk0, const UIResolvedDef& unk1);

	UnknownReturn _createFromResolvedDef(const UIControlFactoryContext& unk0, const UIResolvedDef& unk1, UIControl* unk2, ControlScreenAction& unk3, ui::ChildInsertPosition unk4, bool unk5);

	UnknownReturn _createGradientRenderer(CustomRenderComponent& unk0, const UIResolvedDef& unk1);

	UnknownReturn _createGrid(const UIControlFactoryContext& unk0, UIControl& unk1, const UIResolvedDef& unk2);

	UnknownReturn _createGridPageIndicator(const UIControlFactoryContext& unk0, UIControl& unk1, const UIResolvedDef& unk2);

	UnknownReturn _createImage(UIControl& unk0, const UIResolvedDef& unk1);

	UnknownReturn _createImageCycler(UIControl& unk0, const UIResolvedDef& unk1);

	UnknownReturn _createInputPanel(UIControl& unk0, const UIResolvedDef& unk1);

	UnknownReturn _createLabel(UIControl& unk0, const UIResolvedDef& unk1);

	UnknownReturn _createLabelCycler(UIControl& unk0, const UIResolvedDef& unk1);

	UnknownReturn _createPanel(UIControl& unk0, const UIResolvedDef& unk1);

	UnknownReturn _createScreen(UIControl& unk0, const UIResolvedDef& unk1);

	UnknownReturn _createScrollbarBox(UIControl& unk0, const UIResolvedDef& unk1);

	UnknownReturn _createScrollTrack(UIControl& unk0, const UIResolvedDef& unk1);

	UnknownReturn _createScrollView(UIControl& unk0, const UIResolvedDef& unk1);

	UnknownReturn _createSelectionWheel(UIControl& unk0, const UIResolvedDef& unk1);

	UnknownReturn _createSlider(UIControl& unk0, const UIResolvedDef& unk1);

	UnknownReturn _createSliderBox(UIControl& unk0, const UIResolvedDef& unk1);

	UnknownReturn _createStackPanel(UIControl& unk0, const UIResolvedDef& unk1);

	UnknownReturn _createToggle(UIControl& unk0, const UIResolvedDef& unk1);

	UnknownReturn _getFontFromFontType(const std::string& unk0) const;

	UnknownReturn _getFontsFromFontType(const std::string& unk0) const;

	UnknownReturn _populateAnchoredOffsetComponent(const UIResolvedDef& unk0, UIControl& unk1);

	UnknownReturn _populateAnimations(const UIResolvedDef& unk0, UIControl& unk1);

	UnknownReturn _populateButtonComponent(const UIResolvedDef& unk0, UIControl& unk1);

	UnknownReturn _populateCollectionComponent(const UIResolvedDef& unk0, UIControl& unk1);

	UnknownReturn _populateCollectionItemComponent(const UIResolvedDef& unk0, UIControl& unk1);

	UnknownReturn _populateControl(const UIResolvedDef& unk0, UIControl& unk1);

	/// @address {0x45E5810}
	MC void _populateCustomRenderComponent(const UIResolvedDef& unk0, UIControl& unk1);

	UnknownReturn _populateDataBindingComponent(const UIResolvedDef& unk0, UIControl& unk1);

	UnknownReturn _populateDebugRendererComponent(const UIResolvedDef& unk0, UIControl& unk1);

	UnknownReturn _populateDropdownComponent(const UIResolvedDef& unk0, UIControl& unk1);

	UnknownReturn _populateFactoryComponent(const UIControlFactoryContext& unk0, const UIResolvedDef& unk1, UIControl& unk2);

	UnknownReturn _populateFocusComponent(const UIResolvedDef& unk0, UIControl& unk1);

	UnknownReturn _populateFocusContainerComponent(const UIResolvedDef& unk0, UIControl& unk1);

	UnknownReturn _populateGestureComponent(const UIResolvedDef& unk0, UIControl& unk1);

	UnknownReturn _populateGridComponent(const UIControlFactoryContext& unk0, const UIResolvedDef& unk1, UIControl& unk2);

	UnknownReturn _populateGridItemComponent(const UIResolvedDef& unk0, UIControl& unk1);

	UnknownReturn _populateImageCyclingComponent(const UIResolvedDef& unk0, UIControl& unk1);

	UnknownReturn _populateInputComponent(const UIResolvedDef& unk0, UIControl& unk1);

	UnknownReturn _populateLayoutComponent(const UIResolvedDef& unk0, UIControl& unk1);

	UnknownReturn _populatePageIndicatorGridComponent(const UIResolvedDef& unk0, UIControl& unk1);

	UnknownReturn _populatePageIndicatorManagerComponent(const UIResolvedDef& unk0, UIControl& unk1);

	UnknownReturn _populateScreenComponent(const UIResolvedDef& unk0, UIControl& unk1);

	UnknownReturn _populateScrollbarBoxComponent(const UIResolvedDef& unk0, UIControl& unk1);

	UnknownReturn _populateScrollbarComponent(const UIResolvedDef& unk0, UIControl& unk1);

	UnknownReturn _populateScrollViewComponent(const UIResolvedDef& unk0, UIControl& unk1);

	UnknownReturn _populateSelectionWheelComponent(const UIResolvedDef& unk0, UIControl& unk1);

	UnknownReturn _populateSliderBoxComponent(const UIResolvedDef& unk0, UIControl& unk1);

	UnknownReturn _populateSliderComponent(const UIResolvedDef& unk0, UIControl& unk1);

	UnknownReturn _populateSliderGroupManagerComponent(const UIResolvedDef& unk0, UIControl& unk1);

	UnknownReturn _populateSoundComponent(const UIResolvedDef& unk0, UIControl& unk1, bool unk2);

	UnknownReturn _populateSpriteComponent(const UIResolvedDef& unk0, UIControl& unk1);

	UnknownReturn _populateStackPanelComponent(const UIResolvedDef& unk0, UIControl& unk1);

	UnknownReturn _populateTextComponent(const UIResolvedDef& unk0, UIControl& unk1);

	UnknownReturn _populateTextCyclingComponent(const UIResolvedDef& unk0, UIControl& unk1);

	UnknownReturn _populateTextEditComponent(const UIResolvedDef& unk0, UIControl& unk1);

	UnknownReturn _populateTextToSpeechComponent(const UIResolvedDef& unk0, UIControl& unk1, int unk2);

	UnknownReturn _populateTextToSpeechContainerComponent(const UIResolvedDef& unk0, UIControl& unk1);

	UnknownReturn _populateToggleComponent(const UIResolvedDef& unk0, UIControl& unk1);

	UnknownReturn _populateToggleGroupManagerComponent(const UIResolvedDef& unk0, UIControl& unk1);

	UnknownReturn _postCreate(const UIControlFactoryContext& unk0, UIControl& unk1, const UIResolvedDef& unk2);

	UnknownReturn _postCreateGrid(UIControl& unk0);

	UnknownReturn _postCreateImageCycler(UIControl& unk0);

	UnknownReturn _postCreateLabelCycler(UIControl& unk0);

	// float _resolveAnimatedProperty<float>(const UIResolvedDef& unk0, UIControl& unk1, const std::string& unk2);

	// ui::LayoutOffset _resolveAnimatedProperty<ui::LayoutOffset>(const UIResolvedDef& unk0, UIControl& unk1, const std::string& unk2);

	// mce::Color _resolveAnimatedProperty<mce::Color>(const UIResolvedDef& unk0, UIControl& unk1, const std::string& unk2);

	UnknownReturn _resolveTileDirection(const UIResolvedDef& unk0, UIControl& unk1, const std::string& unk2);

	UnknownReturn _setName(UIControl& unk0, const UIResolvedDef& unk1, const std::string& unk2);

	UnknownReturn createControlTree(std::string_view unk0, ControlScreenAction& unk1, UIControl* unk2, ui::ChildInsertPosition unk3, Json::Value* unk4, bool unk5);

	UnknownReturn createControlTree(const UIControl& unk0, UIControl* unk1, ui::ChildInsertPosition unk2);

	UnknownReturn createControlTreeRootOnly(std::string_view unk0, ControlScreenAction& unk1);
};