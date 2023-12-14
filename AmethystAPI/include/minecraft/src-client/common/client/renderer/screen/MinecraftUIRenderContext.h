#pragma once
#include <stdint.h>

class ClientInstance;
class ScreenContext;
class UIScene;

class MinecraftUIRenderContext {
private:
    uintptr_t **vtable;

public:
    // 48 89 5C 24 ? 48 89 74 24 ? 48 89 4C 24 ? 57 48 83 EC ? 49 8B F9 48 8B DA 48 8B F1 48 8D 05
    typedef MinecraftUIRenderContext*(__thiscall* _MinecraftUIRenderContext)(MinecraftUIRenderContext*, ClientInstance&, ScreenContext&, const UIScene&);
    MinecraftUIRenderContext(ClientInstance&, ScreenContext&, const UIScene&);

public:
    // vfuncs:
    // ~MinecraftUIRenderContext();
    // getLineLength(Font &, std::string const &, float, bool);
    // getTextAlpha(void);
    // setTextAlpha(float);
    // drawDebugText(RectangleArea const &, std::string const &, mce::Color const &, float, ui::TextAlignment, TextMeasureData const &, CaretMeasureData const &);
    // drawText(Font &, RectangleArea const &, std::string const &, mce::Color const &, float, ui::TextAlignment, TextMeasureData const &, CaretMeasureData const &);
    // flushText(float);
    // drawImage(mce::TexturePtr const &, glm::vec<2, float, (glm::qualifier)0> const &, glm::vec<2, float, (glm::qualifier)0> const &, glm::vec<2, float, (glm::qualifier)0> const &, glm::vec<2, float, (glm::qualifier)0> const &);
    // drawNineslice(mce::TexturePtr const &, NinesliceInfo const &);
    // flushImages(mce::Color const &, float, HashedString const &);
    // beginSharedMeshBatch(ComponentRenderBatch &);
    // endSharedMeshBatch(ComponentRenderBatch &);
    // drawRectangle(RectangleArea const &, mce::Color const &, float, int);
    // fillRectangle(RectangleArea const &, mce::Color const &, float);
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
    // getTexture(ResourceLocation const &, bool);
    // getZippedTexture(Core::Path const &, ResourceLocation const &, bool);
    // unloadTexture(ResourceLocation const &);
    // getUITextureInfo(ResourceLocation const &, bool);
    // touchTexture(ResourceLocation const &);
    // getMeasureStrategy(void);
    // snapImageSizeToGrid(glm::vec<2, float, (glm::qualifier)0> &);
    // snapImagePositionToGrid(glm::vec<2, float, (glm::qualifier)0> &);
    // notifyImageEstimate(ulong);
};