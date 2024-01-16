#pragma once
#include "glm/glm.hpp"

#include "core/math/Color.h"
#include "core/string/StringHash.h"
#include "common/world/phys/Vec2.h"
#include "common/client/game/ClientInstance.h"
#include "common/client/renderer/screen/ScreenContext.h"
#include "common/client/renderer/NinesliceInfo.h"

#include <cstdint>
#include <string>

using IClientInstance = ClientInstance;
class UIScene;
class Font;

#pragma pack(push, 4)
struct RectangleArea {
    float _x0;
    float _x1;
    float _y0;
    float _y1;
};
#pragma pack(pop)

namespace ui {
enum TextAlignment : uint8_t {
    Left = 0x0,
    Right = 0x1,
    Center = 0x2
};
}

#pragma pack(push, 4)
struct TextMeasureData {
    float fontSize;
    int linePadding;
    bool renderShadow;
    bool showColorSymbol;
    bool hideHyphen;
};
#pragma pack(pop)

#pragma pack(push, 4)
struct CaretMeasureData {
    int position;
    bool shouldRender;
};
#pragma pack(pop)

namespace mce {
class TexturePtr;
};

class ResourceLocation;

class MinecraftUIRenderContext {
private:
    uintptr_t** vtable;

public:
    IClientInstance* mClient;      // this + 8
    ScreenContext* mScreenContext; // this + 16
private:
    bool padding0[224];

public:
    void* mCurrentScene; // const UIScene*, this + 248

public:
    // 48 89 5C 24 ? 48 89 74 24 ? 48 89 4C 24 ? 57 48 83 EC ? 49 8B F9 48 8B DA 48 8B F1 48 8D 05
    typedef MinecraftUIRenderContext*(__thiscall* _MinecraftUIRenderContext)(MinecraftUIRenderContext*, IClientInstance&, ScreenContext&, const UIScene&);
    MinecraftUIRenderContext(IClientInstance& client, ScreenContext& screenContext, const UIScene& currentScene);

public:
    // vfuncs:
    // ~MinecraftUIRenderContext();

    float getLineLength(Font& font, const std::string& text, float fontSize, bool showColorSymbol);
    float getTextAlpha();
    void setTextAlpha(float alpha);
    void drawDebugText(const RectangleArea* rect, const std::string* text, const mce::Color* color, float alpha, ui::TextAlignment alignment, const TextMeasureData* textData, const CaretMeasureData* caretData);
    void drawText(Font& font, const RectangleArea& rect, const std::string& text, const mce::Color& color, float alpha, ui::TextAlignment alignment, const TextMeasureData& textData, const CaretMeasureData& caretData);
    void flushText(float deltaTime);
    void drawImage(const mce::TexturePtr& texture, const glm::tvec2<float>* position, const glm::tvec2<float>* size, glm::tvec2<float>* uv, glm::tvec2<float>* uvSize, int degree);
    void drawNineslice(const mce::TexturePtr* texture, const NinesliceInfo* nineslice);
    void flushImages(const mce::Color& color, float alpha, const HashedString& materialNameHash);

    // beginSharedMeshBatch(ComponentRenderBatch &);
    // endSharedMeshBatch(ComponentRenderBatch &);

    void drawRectangle(const RectangleArea* rect, const mce::Color* color, float alpha, int thickness);
    void fillRectangle(const RectangleArea* rect, const mce::Color* color, float alpha);

    // increaseStencilRef(void);
    // decreaseStencilRef(void);
    // resetStencilRef(void);
    // fillRectangleStencil(RectangleArea const &);
    // enableScissorTest(RectangleArea const &);
    // disableScissorTest(void);
    // setClippingRectangle(RectangleArea const &);
    // setFullClippingRectangle(void);
    // saveCurrentClippingRectangle(void);
    // restoreSavedClippingRectangle(void);
    // getFullClippingRectangle(void);
    // updateCustom(gsl::not_null<CustomRenderComponent *>);
    // renderCustom(gsl::not_null<CustomRenderComponent *>, int, RectangleArea &);
    // cleanup(void);
    // removePersistentMeshes(void);

    mce::TexturePtr* getTexture(mce::TexturePtr* result, const ResourceLocation* resourceLocation, bool forceReload);

    // getZippedTexture(Core::Path const &, ResourceLocation const &, bool);
    // unloadTexture(ResourceLocation const &);
    // getUITextureInfo(ResourceLocation const &, bool);
    // touchTexture(ResourceLocation const &);
    // getMeasureStrategy(void);
    // snapImageSizeToGrid(glm::vec<2, float, (glm::qualifier)0> &);
    // snapImagePositionToGrid(glm::vec<2, float, (glm::qualifier)0> &);
    // notifyImageEstimate(ulong);
};