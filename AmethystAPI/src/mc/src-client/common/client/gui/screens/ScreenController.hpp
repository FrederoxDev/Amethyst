/// @symbolgeneration
#pragma once
#include "mc/src-deps/core/string/StringHash.hpp"
#include "mc/src-deps/input/InputHandler.hpp"
#include <amethyst/Imports.hpp>

class UIPropertyBag;
using UiPropertyBag = UIPropertyBag;
class ScreenEvent;
class ScreenControllerProxy;
class FlyingItemCommand;
class SelectNavigationTabCommand;
class RawInputScreenEventData;
class FocusMoveScreenEventData;
class InputModeChangeScreenEventData;
class HoloInputModeChangeScreenEventData;
class PointerHeldScreenEventData;
class TextEditScreenEventData;
class ToggleChangeEventData;
class TextEditSelectedStateChangeEventData;
class TaskGroup;
class BlockPos;
struct ActorUniqueID;

namespace Json {
class Value;
}

namespace ui {
enum class SceneType {
    None                      = 0,
    DefaultScene              = 1u << 0,
    StoreScene                = 1u << 1,
    StoreHomeScene            = 1u << 2,
    StoreInventoryScene       = 1u << 3,
    StartMenuScene            = 1u << 4,
    SettingsScene             = 1u << 5,
    LibraryItemScene          = 1u << 6,
    LibraryModalScene         = 1u << 7,
    ProfileScene              = 1u << 8,
    DressingRoomScene         = 1u << 9,
    AchievementScene          = 1u << 10,
    NoInterrupt               = 1u << 11,
    OreUi                     = 1u << 12,
    PlayScreen                = 1u << 13,
    ProgressScene             = 1u << 14,
    PauseScene                = 1u << 15,
    RealmsPlusPdpScene        = 1u << 16,
    MultiControllerInputScene = 1u << 17,
    HudScene                  = 1u << 18,
    MarketplacePlusPdpScene   = 1u << 19,
    DisplayErrorLogScene      = 1u << 20,
};

enum class ViewRequest : uint32_t {
    None = 0,
    Refresh = 1u << 0,
    PointerHeldEventsRequest = 1u << 1,
    PointerHeldEventsCancel = 1u << 2,
    DelayedFocusRefresh = 1u << 3,
    Exit = 1u << 4,
    ConsumeEvent = 1u << 5,
};

enum class DirtyFlag {
    None = 0,
    UpdateBinds = 1u << 0,
    UpdateCurrentFocus = 1u << 1,
    GlobalLayout = 1u << 2,
    LayoutChanged = 1u << 3,
    UpdateToDefaultFocus = 1u << 4,
    All = UpdateBinds | UpdateCurrentFocus | GlobalLayout,
};

class GameEventNotification {};
}

class ScreenViewCommand {
    std::function<void(FlyingItemCommand&)> sendFlyingItems;
    std::function<void(SelectNavigationTabCommand&)> selectNavigationTab;
    std::function<void(void)> openKeyboard;
    std::function<void(void)> closeKeyboard;
    std::function<void(const std::string&)> selectControl;
    std::function<void(const std::string&)> selectVisibleControl;
    std::function<void(const std::string&, bool)> focusControl;
    std::function<void(const std::string&)> setFocusedTextBoxText;
    std::function<bool(const std::string&)> isFocusWithin;
    std::function<bool(const std::string&)> isSelected;
    std::function<void(const std::string&, bool)> scrollToControl;
    std::function<void(const std::string&)> scrollToControlAndSelect;
    std::function<void(const std::string&, int)> focusCollectionItem;
    std::function<bool(const std::string&, int, int)> scrollToGridItemOffset;
    std::function<bool(const std::string&, int, const std::string&, int, int)> scrollToGridItemOffsetCollectionIndex;
    std::function<void(const std::string&)> resetScrollWithin;
    std::function<void(const std::string&, const std::string&, int)> setFocusToFocusIdWhenVisible;
    std::function<void(void)> prepareFocusForModalPopup;
    std::function<void(void)> updateTTSForSlider;
    std::function<void(void)> forceRepeatTTS;
    std::function<void(float)> setCustomObfuscatedTime;
    std::function<void(const std::string&)> triggerAnimationEvent;
};

class IScreenController {
public:
    virtual ~IScreenController() = 0;
    virtual void preFrameTick() = 0;
    virtual ui::DirtyFlag tick() = 0;
    virtual ui::ViewRequest handleEvent(ScreenEvent& event) = 0;
    virtual std::optional<std::string> getRoute() = 0;
    virtual void setScreenState(const std::vector<std::pair<std::string_view, std::string_view>>& state) = 0;
};

/// @vptr {0x4CCA2A0}
class ScreenController {
public:
    MC static uintptr_t $vtable_for_this;

    enum class PreviousButtonStateRequirement : int32_t {
        Any = 0x0000,
        Down = 0x0001,
        Up = 0x0002,
        NotDown = 0x0003,
        NotUp = 0x0004,
    };

    struct ButtonEventCallbackKeyHasher {
    public:
        uint64_t operator()(const std::tuple<uint32_t, ButtonState>& value) const {
            return std::get<0>(value) ^ static_cast<uint64_t>(std::get<1>(value));
        }
    };

    std::function<void(const std::string&, const UIPropertyBag&)> mControlCreateCallback;
    std::function<void(const std::string&, const std::string&)> mControlDestroyCallback;
    std::function<void(const std::string&)> mControlDestroyAllCallback;
    std::function<void(const std::string&)> mScreenViewSendManualInputEventCallback;
    std::unique_ptr<ScreenControllerProxy> mProxy;
    bool mCreateInitialized;
    bool mInitialized;
    bool mUsesErrorInfo;
    ScreenViewCommand mScreenViewCommand;
    std::unordered_map<std::tuple<uint32_t, ButtonState>, std::vector<std::tuple<ScreenController::PreviousButtonStateRequirement, std::function<ui::ViewRequest(UIPropertyBag*)>>>, ScreenController::ButtonEventCallbackKeyHasher, std::equal_to<std::tuple<uint32_t, ButtonState>>, std::allocator<std::pair<std::tuple<uint32_t, ButtonState> const, std::vector<std::tuple<ScreenController::PreviousButtonStateRequirement, std::function<ui::ViewRequest(UIPropertyBag*)>>>>>> mButtonEventCallbackMap;
    std::unordered_map<uint32_t, std::vector<std::function<ui::ViewRequest(UIPropertyBag*)>>> mButtonInteractedEventCallbackMap;
    std::function<ui::ViewRequest(RawInputScreenEventData&)> mRawInputEventHandlerCallback;
    std::vector<std::function<ui::ViewRequest(FocusMoveScreenEventData&)>> mFocusMoveEventCallbacks;
    std::vector<std::function<ui::ViewRequest(InputModeChangeScreenEventData&)>> mInputModeChangedEventCallbacks;
    std::vector<std::function<ui::ViewRequest(HoloInputModeChangeScreenEventData&)>> mHoloInputModeChangedEventCallbacks;
    std::vector<std::function<ui::ViewRequest(PointerHeldScreenEventData&)>> mPointerHeldEventCallbacks;
    std::unordered_map<uint32_t, std::vector<std::tuple<bool, std::function<ui::ViewRequest(TextEditScreenEventData&, int)>>>> mTextEditEventCallbackMap;
    std::unordered_map<uint32_t, std::vector<std::function<ui::ViewRequest(ToggleChangeEventData&)>>> mToggleChangeEventCallbackMap;
    std::unordered_map<uint32_t, std::vector<std::function<ui::ViewRequest(TextEditSelectedStateChangeEventData&)>>> mTextEditSelectedStateChangeEventCallbackMap;
    std::vector<std::shared_ptr<ScreenController>> mSubControllers;
    std::unordered_map<uint32_t, std::vector<std::tuple<bool, std::function<ui::ViewRequest(int, float)>>>> mSliderChangeEventCallbackMap;
    std::unordered_map<uint32_t, std::vector<std::function<ui::ViewRequest(void)>>> mAnimationEventCallbackMap;
    std::unordered_map<uint32_t, std::vector<std::function<ui::ViewRequest(int, int, UIPropertyBag&)>>> mClippedCollectionEventCallbackMap;
    std::unordered_map<uint32_t, std::vector<std::function<ui::ViewRequest(bool, UIPropertyBag&)>>> mClipStateChangeEventCallbackMap;
    std::unordered_map<uint32_t, std::vector<std::function<ui::ViewRequest(void)>>> mCustomRendererEventHandlerCallbackMap;
    std::unordered_map<uint32_t, std::function<void(const std::string&, UIPropertyBag&)>> mBindCallbacks;
    std::unordered_map<uint32_t, std::function<void(int, const std::string&, UIPropertyBag&)>> mCollectionBindCallbacks;
    std::unordered_map<uint32_t, std::function<void(const std::string&, int, const std::string&, UIPropertyBag&)>> mAnyCollectionBindCallbacks;
    std::unique_ptr<TaskGroup> mTaskGroup;

    /// @signature {48 89 5C 24 ? 48 89 6C 24 ? 56 57 41 56 48 83 EC ? 0F B6 DA}
    MC ScreenController(bool useTaskGroup);

    /** @vidx {00} */ MC virtual ~ScreenController();
    /** @vidx {01} */ MC virtual void preFrameTick();
    /** @vidx {02} */ MC virtual ui::DirtyFlag tick();
    /** @vidx {03} */ MC virtual ui::ViewRequest handleEvent(ScreenEvent&);
    /** @vidx {04} */ MC virtual std::optional<std::string> getRoute();
    /** @vidx {05} */ MC virtual void setScreenState(const std::vector<std::pair<std::string_view, std::string_view>>&);
    /** @vidx {06} */ MC virtual void onOpen();
    /** @vidx {07} */ MC virtual void queueTitleNarration();
    /** @vidx {08} */ MC virtual void onTerminate();
    /** @vidx {09} */ MC virtual void onInit();
    /** @vidx {10} */ MC virtual void onDelete();
    /** @vidx {11} */ MC virtual bool canExit();
    /** @vidx {12} */ MC virtual ui::ViewRequest tryExit();
    /** @vidx {13} */ MC virtual void onCreation();
    /** @vidx {14} */ MC virtual void onReload();
    /** @vidx {15} */ MC virtual void onLeave();
    /** @vidx {16} */ MC virtual void leaveScreen(const std::string&);
    /** @vidx {17} */ MC virtual ui::DirtyFlag handleGameEventNotification(ui::GameEventNotification);
    /** @vidx {19} */ MC virtual bool bind(const std::string&, uint32_t, const std::string&, UIPropertyBag&);
    /** @vidx {18} */ MC virtual bool bind(const std::string& collectionName, uint32_t collectionNameHash, int collectionIndex, const std::string& bindingName, uint32_t bindingNameHash, const std::string&, UIPropertyBag& bag);
    /** @vidx {20} */ MC virtual void handleLicenseChanged();
    /** @vidx {21} */ MC virtual void onDictationEvent(const std::string&);
    /** @vidx {22} */ MC virtual void setAssociatedBlockPos(const BlockPos&);
    /** @vidx {23} */ MC virtual void setAssociatedEntityUniqueID(const ActorUniqueID);
    /** @vidx {24} */ MC virtual void setSuspendInput(bool);
    /** @vidx {25} */ MC virtual void setViewCommand(const ScreenViewCommand&);
    /** @vidx {26} */ MC virtual void addStaticScreenVars(Json::Value&);
    /** @vidx {27} */ MC virtual std::string getAdditionalScreenInfo();
    /** @vidx {28} */ MC virtual std::string getTelemetryOverride();
    /** @vidx {29} */ MC virtual void addEventProperties(std::unordered_map<std::string, std::string>&);
    /** @vidx {30} */ MC virtual ui::SceneType getSceneType();
    /** @vidx {31} */ MC virtual int getScreenVersion();
    /** @vidx {32} */ MC virtual uint32_t getSceneId();
    /** @vidx {33} */ MC virtual bool screenHandlesGamepadMenuButton();
    /** @vidx {34} */ MC virtual ScreenControllerProxy* getProxy();
    /** @vidx {35} */ MC virtual void onEntered();
    /** @vidx {36} */ MC virtual void onScreenPushedAbove();
    /** @vidx {37} */ MC virtual void onEntering();
    /** @vidx {38} */ MC virtual bool _doesScreenHaveExitBehavior();

// Non-virtuals
public:
    /// @signature {89 54 24 ? 55 53 56 57 41 56 48 8B EC 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 49 8B F0 8B DA 4C 8B C9 4C 89 45 ? 48 8D B9 ? ? ? ? 44 0F B6 C2 48 B8 ? ? ? ? ? ? ? ? 4C 33 C0 48 B9 ? ? ? ? ? ? ? ? 4C 0F AF C1 0F B6 45 ? 4C 33 C0 4C 0F AF C1 0F B6 45 ? 4C 33 C0 4C 0F AF C1 0F B6 45 ? 4C 33 C0 4C 0F AF C1 49 8B 89 ? ? ? ? 49 23 C8 48 C1 E1 ? 49 8B 81 ? ? ? ? 48 03 C1 48 8B 48 ? 49 8B 91 ? ? ? ? 45 33 F6 48 3B CA 74 ? 48 8B 00 3B 59 ? 74 ? 48 3B C8 74 ? 48 8B 49 ? 3B 59 ? 75 ? EB ? 49 8B CE 48 85 C9 48 0F 44 CA 48 3B CA 74 ? 48 83 C1 ? 48 8B D6 E8 ? ? ? ? E9 ? ? ? ? 0F 57 C9 F3 0F 7F 4D ? 4C 89 75 ? 4C 8B C6 33 D2 48 8D 4D ? E8 ? ? ? ? 89 5D ? 4C 8B 45 ? 4C 89 75 ? 48 8B 55 ? 4C 89 75 ? 48 8B 45 ? 4C 89 75 ? 48 89 45 ? 48 89 55 ? 4C 89 45 ? 4C 8D 45 ? 48 8D 55 ? 48 8B CF E8 ? ? ? ? 90 48 8D 4D ? E8 ? ? ? ? 90 48 8B 5D ? 48 85 DB 74 ? 48 8B 7D ? 48 3B DF 74 ? 48 8B 4B ? 48 85 C9 74 ? 48 8B 01 48 3B CB 0F 95 C2 48 8B 40 ? FF 15 ? ? ? ? 4C 89 73 ? 48 83 C3 ? 48 3B DF 75 ? 48 8B 5D ? 48 8B 55 ? 48 2B D3 48 83 E2 ? 48 8B C3 48 81 FA ? ? ? ? 72 ? 48 83 C2 ? 48 8B 5B ? 48 2B C3 48 83 C0 ? 48 83 F8 ? 76 ? FF 15 ? ? ? ? CC 48 8B CB E8 ? ? ? ? 90 48 8B 4E ? 48 85 C9 74 ? 48 8B 01 48 3B CE 0F 95 C2 48 8B 40 ? FF 15 ? ? ? ? 4C 89 76 ? 48 8B 4D ? 48 33 CC E8 ? ? ? ? 48 81 C4 ? ? ? ? 41 5E 5F 5E 5B 5D C3 CC CC CC CC CC CC CC 48 89 5C 24 ? 57}
    MC void registerButtonInteractedHandler(uint32_t id, std::function<ui::ViewRequest(UIPropertyBag*)> callback);

    /// @signature {48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 54 41 55 41 56 41 57 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 0F 10 52}
    MC ui::ViewRequest _handleButtonEvent(ScreenEvent& event);

    /// @signature {4C 8B DC 49 89 5B ? 49 89 73 ? 57 48 81 EC ? ? ? ? 49 8B D8 48 8B FA 48 8D B1 ? ? ? ? 48 8D 44 24 ? 49 89 43 ? 49 C7 43 ? ? ? ? ? 49 8B 49 ? 48 85 C9 74 ? 48 8B 01 48 8D 54 24 ? 48 8B 00 FF 15 ? ? ? ? 48 89 44 24 ? 48 8D 44 24 ? 48 89 84 24 ? ? ? ? 48 C7 84 24 ? ? ? ? ? ? ? ? 48 8B 4B ? 48 85 C9 74 ? 48 8B 01 48 8D 54 24 ? 48 8B 00 FF 15 ? ? ? ? 48 89 84 24 ? ? ? ? 8B 07 89 84 24 ? ? ? ? 4C 8D 4C 24 ? 4C 8D 84 24 ? ? ? ? 48 8D 94 24 ? ? ? ? 48 8B CE E8 ? ? ? ? 90 48 8B 8C 24 ? ? ? ? 48 85 C9 74 ? 48 8B 01 48 8D 54 24 ? 48 3B CA 0F 95 C2 48 8B 40 ? FF 15 ? ? ? ? 48 C7 84 24 ? ? ? ? ? ? ? ? 48 8B 4C 24 ? 48 85 C9 74 ? 48 8B 01 48 8D 54 24 ? 48 3B CA 0F 95 C2 48 8B 40 ? FF 15 ? ? ? ? 4C 8D 9C 24 ? ? ? ? 49 8B 5B ? 49 8B 73 ? 49 8B E3 5F C3 CC CC CC CC CC CC 48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 49 8B F0 48 8B DA 48 8B F9 48 8B 49 ? 48 85 C9 75}
    MC void bindString(const StringHash& bindingName, const std::function<std::string()>& callback, const std::function<bool()>& condition);

    /// @signature {4C 8B DC 49 89 5B ? 49 89 73 ? 57 48 81 EC ? ? ? ? 49 8B D8 48 8B FA 48 8D B1 ? ? ? ? 48 8D 44 24 ? 49 89 43 ? 49 C7 43 ? ? ? ? ? 49 8B 49 ? 48 85 C9 74 ? 48 8B 01 48 8D 54 24 ? 48 8B 00 FF 15 ? ? ? ? 48 89 44 24 ? 48 8D 44 24 ? 48 89 84 24 ? ? ? ? 48 C7 84 24 ? ? ? ? ? ? ? ? 48 8B 4B ? 48 85 C9 74 ? 48 8B 01 48 8D 54 24 ? 48 8B 00 FF 15 ? ? ? ? 48 89 84 24 ? ? ? ? 8B 07 89 84 24 ? ? ? ? 4C 8D 4C 24 ? 4C 8D 84 24 ? ? ? ? 48 8D 94 24 ? ? ? ? 48 8B CE E8 ? ? ? ? 90 48 8B 8C 24 ? ? ? ? 48 85 C9 74 ? 48 8B 01 48 8D 54 24 ? 48 3B CA 0F 95 C2 48 8B 40 ? FF 15 ? ? ? ? 48 C7 84 24 ? ? ? ? ? ? ? ? 48 8B 4C 24 ? 48 85 C9 74 ? 48 8B 01 48 8D 54 24 ? 48 3B CA 0F 95 C2 48 8B 40 ? FF 15 ? ? ? ? 4C 8D 9C 24 ? ? ? ? 49 8B 5B ? 49 8B 73 ? 49 8B E3 5F C3 CC CC CC CC CC CC 48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 49 8B F0 48 8B DA 48 8B F9 48 8B 49 ? 48 85 C9 0F 84}
    MC void bindBool(const StringHash& bindingName, const std::function<bool()>& callback, const std::function<bool()>& condition);

    /// @signature {4C 8B DC 49 89 5B ? 49 89 73 ? 57 48 81 EC ? ? ? ? 49 8B D8 48 8B FA 48 8D B1 ? ? ? ? 48 8D 44 24 ? 49 89 43 ? 49 C7 43 ? ? ? ? ? 49 8B 49 ? 48 85 C9 74 ? 48 8B 01 48 8D 54 24 ? 48 8B 00 FF 15 ? ? ? ? 48 89 44 24 ? 48 8D 44 24 ? 48 89 84 24 ? ? ? ? 48 C7 84 24 ? ? ? ? ? ? ? ? 48 8B 4B ? 48 85 C9 74 ? 48 8B 01 48 8D 54 24 ? 48 8B 00 FF 15 ? ? ? ? 48 89 84 24 ? ? ? ? 8B 07 89 84 24 ? ? ? ? 4C 8D 4C 24 ? 4C 8D 84 24 ? ? ? ? 48 8D 94 24 ? ? ? ? 48 8B CE E8 ? ? ? ? 90 48 8B 8C 24 ? ? ? ? 48 85 C9 74 ? 48 8B 01 48 8D 54 24 ? 48 3B CA 0F 95 C2 48 8B 40 ? FF 15 ? ? ? ? 48 C7 84 24 ? ? ? ? ? ? ? ? 48 8B 4C 24 ? 48 85 C9 74 ? 48 8B 01 48 8D 54 24 ? 48 3B CA 0F 95 C2 48 8B 40 ? FF 15 ? ? ? ? 4C 8D 9C 24 ? ? ? ? 49 8B 5B ? 49 8B 73 ? 49 8B E3 5F C3 CC CC CC CC CC CC 48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B F9 49 8B F0 48 8B 49 ? 48 8B DA 48 85 C9 74 ? 48 8B 01 48 8B 40 ? FF 15 ? ? ? ? 84 C0 74 ? 48 8B 4F ? 48 85 C9 74 ? 48 8B 01 48 8B 40 ? FF 15 ? ? ? ? 48 83 7B ? ? 48 8B C3}
    MC void bindFloat(const StringHash& bindingName, const std::function<float()>& callback, const std::function<bool()>& condition);

    /// @signature {4C 8B DC 49 89 5B ? 49 89 73 ? 57 48 81 EC ? ? ? ? 49 8B D8 48 8B FA 48 8D B1 ? ? ? ? 48 8D 44 24 ? 49 89 43 ? 49 C7 43 ? ? ? ? ? 49 8B 49 ? 48 85 C9 74 ? 48 8B 01 48 8D 54 24 ? 48 8B 00 FF 15 ? ? ? ? 48 89 44 24 ? 48 8D 44 24 ? 48 89 84 24 ? ? ? ? 48 C7 84 24 ? ? ? ? ? ? ? ? 48 8B 4B ? 48 85 C9 74 ? 48 8B 01 48 8D 54 24 ? 48 8B 00 FF 15 ? ? ? ? 48 89 84 24 ? ? ? ? 8B 07 89 84 24 ? ? ? ? 4C 8D 4C 24 ? 4C 8D 84 24 ? ? ? ? 48 8D 94 24 ? ? ? ? 48 8B CE E8 ? ? ? ? 90 48 8B 8C 24 ? ? ? ? 48 85 C9 74 ? 48 8B 01 48 8D 54 24 ? 48 3B CA 0F 95 C2 48 8B 40 ? FF 15 ? ? ? ? 48 C7 84 24 ? ? ? ? ? ? ? ? 48 8B 4C 24 ? 48 85 C9 74 ? 48 8B 01 48 8D 54 24 ? 48 3B CA 0F 95 C2 48 8B 40 ? FF 15 ? ? ? ? 4C 8D 9C 24 ? ? ? ? 49 8B 5B ? 49 8B 73 ? 49 8B E3 5F C3 CC CC CC CC CC CC 40 53 55 56 57 41 56 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 4C 8B B4 24 ? ? ? ? 48 8B F9 48 8B 49 ? 49 8B D9 44 89 44 24 ? 41 8B F0 48 8B EA 48 85 C9 75 ? FF 15 ? ? ? ? CC 48 8B 01 4C 8D 44 24 ? 48 8B 40 ? FF 15 ? ? ? ? 84 C0 74 ? 48 8B 4F ? 89 74 24 ? 48 85 C9 75 ? FF 15 ? ? ? ? CC 48 8B 01 4C 8D 44 24 ? 48 8B D5 48 8B 40 ? FF 15 ? ? ? ? 48 83 7B ? ? 89 44 24}
    MC void bindIntForAnyCollection(const StringHash& bindingName, const std::function<int(const std::string& collection, int index)>& callback, const std::function<bool(const std::string& collection, int index)>& condition);

    /// @signature {4C 8B DC 49 89 5B ? 49 89 6B ? 49 89 73 ? 57 48 81 EC ? ? ? ? 49 8B D9 49 8B F8 48 8B F2 48 8D A9 ? ? ? ? 48 8D 44 24 ? 49 89 43 ? 49 C7 43 ? ? ? ? ? 48 8B 84 24 ? ? ? ? 48 8B 48 ? 48 85 C9 74 ? 48 8B 01 48 8D 54 24 ? 48 8B 00 FF 15 ? ? ? ? 48 89 44 24 ? 48 8D 44 24 ? 48 89 84 24 ? ? ? ? 48 C7 84 24 ? ? ? ? ? ? ? ? 48 8B 4B ? 48 85 C9 74 ? 48 8B 01 48 8D 54 24 ? 48 8B 00 FF 15 ? ? ? ? 48 89 84 24 ? ? ? ? 8B 06 33 07 89 84 24 ? ? ? ? 4C 8D 4C 24 ? 4C 8D 84 24 ? ? ? ? 48 8D 94 24 ? ? ? ? 48 8B CD E8 ? ? ? ? 90 48 8B 8C 24 ? ? ? ? 48 85 C9 74 ? 48 8B 01 48 8D 54 24 ? 48 3B CA 0F 95 C2 48 8B 40 ? FF 15 ? ? ? ? 48 C7 84 24 ? ? ? ? ? ? ? ? 48 8B 4C 24 ? 48 85 C9 74 ? 48 8B 01 48 8D 54 24 ? 48 3B CA 0F 95 C2 48 8B 40 ? FF 15 ? ? ? ? 4C 8D 9C 24 ? ? ? ? 49 8B 5B ? 49 8B 6B ? 49 8B 73 ? 49 8B E3 5F C3 CC 48 89 5C 24 ? 55 56 57 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 48 8B F9}
    MC void bindIntForCollection(const StringHash& bindingName, const std::string& collectionName, const std::function<int(int index)>& callback, const std::function<bool(int index)>& condition);

    /// @signature {4C 8B DC 49 89 5B ? 49 89 73 ? 57 48 81 EC ? ? ? ? 49 8B D8 48 8B FA 48 8D B1 ? ? ? ? 48 8D 44 24 ? 49 89 43 ? 49 C7 43 ? ? ? ? ? 49 8B 49 ? 48 85 C9 74 ? 48 8B 01 48 8D 54 24 ? 48 8B 00 FF 15 ? ? ? ? 48 89 44 24 ? 48 8D 44 24 ? 48 89 84 24 ? ? ? ? 48 C7 84 24 ? ? ? ? ? ? ? ? 48 8B 4B ? 48 85 C9 74 ? 48 8B 01 48 8D 54 24 ? 48 8B 00 FF 15 ? ? ? ? 48 89 84 24 ? ? ? ? 8B 07 89 84 24 ? ? ? ? 4C 8D 4C 24 ? 4C 8D 84 24 ? ? ? ? 48 8D 94 24 ? ? ? ? 48 8B CE E8 ? ? ? ? 90 48 8B 8C 24 ? ? ? ? 48 85 C9 74 ? 48 8B 01 48 8D 54 24 ? 48 3B CA 0F 95 C2 48 8B 40 ? FF 15 ? ? ? ? 48 C7 84 24 ? ? ? ? ? ? ? ? 48 8B 4C 24 ? 48 85 C9 74 ? 48 8B 01 48 8D 54 24 ? 48 3B CA 0F 95 C2 48 8B 40 ? FF 15 ? ? ? ? 4C 8D 9C 24 ? ? ? ? 49 8B 5B ? 49 8B 73 ? 49 8B E3 5F C3 CC CC CC CC CC CC 40 53 55 56 57 41 56 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 49 8B D9 41 8B E8}
    MC void bindBoolForAnyCollection(const StringHash& bindingName, const std::function<bool(const std::string& collection, int index)>& callback, const std::function<bool(const std::string& collection, int index)>& condition);

    /// @signature {4C 8B DC 49 89 5B ? 49 89 73 ? 57 48 81 EC ? ? ? ? 49 8B D8 48 8B FA 48 8D B1 ? ? ? ? 48 8D 44 24 ? 49 89 43 ? 49 C7 43 ? ? ? ? ? 49 8B 49 ? 48 85 C9 74 ? 48 8B 01 48 8D 54 24 ? 48 8B 00 FF 15 ? ? ? ? 48 89 44 24 ? 48 8D 44 24 ? 48 89 84 24 ? ? ? ? 48 C7 84 24 ? ? ? ? ? ? ? ? 48 8B 4B ? 48 85 C9 74 ? 48 8B 01 48 8D 54 24 ? 48 8B 00 FF 15 ? ? ? ? 48 89 84 24 ? ? ? ? 8B 07 89 84 24 ? ? ? ? 4C 8D 4C 24 ? 4C 8D 84 24 ? ? ? ? 48 8D 94 24 ? ? ? ? 48 8B CE E8 ? ? ? ? 90 48 8B 8C 24 ? ? ? ? 48 85 C9 74 ? 48 8B 01 48 8D 54 24 ? 48 3B CA 0F 95 C2 48 8B 40 ? FF 15 ? ? ? ? 48 C7 84 24 ? ? ? ? ? ? ? ? 48 8B 4C 24 ? 48 85 C9 74 ? 48 8B 01 48 8D 54 24 ? 48 3B CA 0F 95 C2 48 8B 40 ? FF 15 ? ? ? ? 4C 8D 9C 24 ? ? ? ? 49 8B 5B ? 49 8B 73 ? 49 8B E3 5F C3 CC CC CC CC CC CC 40 53 55 56 57 41 56 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 4C 8B B4 24 ? ? ? ? 48 8B F9 48 8B 49 ? 49 8B D9 44 89 44 24 ? 41 8B F0 48 8B EA 48 85 C9 75 ? FF 15 ? ? ? ? CC 48 8B 01 4C 8D 44 24 ? 48 8B 40 ? FF 15 ? ? ? ? 84 C0 74 ? 48 8B 4F ? 89 74 24 ? 48 85 C9 75 ? FF 15 ? ? ? ? CC 48 8B 01 4C 8D 44 24 ? 48 8B D5 48 8B 40 ? FF 15 ? ? ? ? 48 83 7B ? ? 48 8B C3}
    MC void bindFloatForAnyCollection(const StringHash& bindingName, const std::function<float(const std::string& collection, int index)>& callback, const std::function<bool(const std::string& collection, int index)>& condition);
};

static_assert(sizeof(ScreenController) == 0xA98);