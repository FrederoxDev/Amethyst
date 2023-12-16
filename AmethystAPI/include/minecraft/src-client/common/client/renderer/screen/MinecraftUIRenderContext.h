#pragma once
#include <stdint.h>
#include <string>
#include "minecraft/src-deps/core/math/Color.h"
#include "minecraft/src-client/common/client/game/ClientInstance.h"

using IClientInstance = ClientInstance;
class ScreenContext;
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
    char undefined;        
};
#pragma pack(pop)

#pragma pack(push, 4)
struct CaretMeasureData {
    int position;        
    bool shouldRender;   
    char undefined1;   
    char undefined2;  
    char undefined3;   
};
#pragma pack(pop)

class MinecraftUIRenderContext {
private:
    uintptr_t **vtable;

public:
    // 48 89 5C 24 ? 48 89 74 24 ? 48 89 4C 24 ? 57 48 83 EC ? 49 8B F9 48 8B DA 48 8B F1 48 8D 05
    typedef MinecraftUIRenderContext*(__thiscall* _MinecraftUIRenderContext)(MinecraftUIRenderContext*, IClientInstance&, ScreenContext&, const UIScene&);
    MinecraftUIRenderContext(IClientInstance& client, ScreenContext& screenContext, const UIScene& currentScene);

public:
    // vfuncs:
    // ~MinecraftUIRenderContext();
    uint64_t getLineLength(Font& font, const std::string& text, float fontSize, bool showColorSymbol);
    float getTextAlpha();
    void setTextAlpha(float alpha);
    void drawDebugText(const RectangleArea& rect, const std::string& text, const mce::Color& color, float alpha, ui::TextAlignment alignment, const TextMeasureData& textData, const CaretMeasureData& caretData);
    void drawText(Font& font, const RectangleArea& rect, const std::string& text, const mce::Color& color, float alpha, ui::TextAlignment alignment, const TextMeasureData& textData, const CaretMeasureData& caretData);

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