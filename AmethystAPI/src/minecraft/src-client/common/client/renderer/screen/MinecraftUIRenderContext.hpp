#pragma once
#include "glm/glm.hpp"
#include <gsl/gsl>
#include "minecraft/src-client/common/client/renderer/screen/ScreenContext.hpp"
#include "minecraft/src-deps/core/utility/NonOwnerPointer.hpp"
#include <cstdint>
#include <string>


namespace mce {
class Color;
}

class ClientInstance;
using IClientInstance = ClientInstance;
class UIScene;
class Font;
struct NinesliceInfo;

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
class TextureGroup;
};

namespace Core {
class Path;
}

class ResourceLocation;
class UIScene;
class ComponentRenderBatch;
class CustomRenderComponent;
class HashedString;

class MinecraftUIRenderContext {
public:
    /* this + 8   */ IClientInstance* mClient;
    /* this + 16  */ ScreenContext* mScreenContext;
    /* this + 24  */ std::byte padding24[64];
    /* this + 88  */ Bedrock::NonOwnerPointer<mce::TextureGroup> mTextures;
    /* this + 104  */ std::byte padding80[248 - 104];
    /* this + 248 */ const UIScene* mCurrentScene;

public:
    MinecraftUIRenderContext(IClientInstance& client, ScreenContext& screenContext, const UIScene& currentScene);

public:
    // vfuncs:
    virtual ~MinecraftUIRenderContext();
    virtual float getLineLength(Font& font, const std::string& text, float fontSize, bool showColorSymbol);
    virtual float getTextAlpha();
    virtual void setTextAlpha(float alpha);
    virtual void drawDebugText(const RectangleArea* rect, const std::string* text, const mce::Color* color, float alpha, ui::TextAlignment alignment, const TextMeasureData* textData, const CaretMeasureData* caretData);
    virtual void drawText(Font& font, const RectangleArea& rect, const std::string& text, const mce::Color& color, float alpha, ui::TextAlignment alignment, const TextMeasureData& textData, const CaretMeasureData& caretData);
    virtual void flushText(float deltaTime);
    virtual void drawImage(const mce::TexturePtr& texture, const glm::tvec2<float>* position, const glm::tvec2<float>* size, glm::tvec2<float>* uv, glm::tvec2<float>* uvSize);
    virtual void drawNineslice(const mce::TexturePtr* texture, const NinesliceInfo* nineslice);
    virtual void flushImages(const mce::Color& color, float alpha, const HashedString& materialNameHash);
    virtual void beginSharedMeshBatch(ComponentRenderBatch& renderBatch);
    virtual void endSharedMeshBatch(ComponentRenderBatch& renderBatch);
    virtual void drawRectangle(const RectangleArea& rect, const mce::Color& color, float alpha, int thickness);
    virtual void fillRectangle(const RectangleArea& rect, const mce::Color& color, float alpha);
    virtual void increaseStencilRef();
    virtual void decreaseStencilRef();
    virtual void resetStencilRef();
    virtual void fillRectangleStencil(const RectangleArea& rect);
    virtual void enableScissorTest(const RectangleArea& rect);
    virtual void disableScissorTest();
    virtual void setClippingRectangle(const RectangleArea& rect);
    virtual void setFullClippingRectangle();
    virtual void saveCurrentClippingRectangle();
    virtual void restoreSavedClippingRectangle();
    virtual RectangleArea getFullClippingRectangle();
    virtual bool updateCustom(gsl::not_null<CustomRenderComponent*> customRenderer);
    virtual void renderCustom(gsl::not_null<CustomRenderComponent*> customRenderer, int pass, RectangleArea& renderAABB);
    virtual void cleanup();
    virtual void removePersistentMeshes();
    virtual mce::TexturePtr getTexture(const ResourceLocation& resourceLocation, bool forceReload);
    virtual mce::TexturePtr getZippedTexture(const Core::Path& zippedFolderPath, const ResourceLocation& resourceLocation, bool forceReload);
    virtual void unloadTexture(ResourceLocation const &);
    // getUITextureInfo(ResourceLocation const &, bool);
    // touchTexture(ResourceLocation const &);
    // getMeasureStrategy(void);
    // snapImageSizeToGrid(glm::vec<2, float, (glm::qualifier)0> &);
    // snapImagePositionToGrid(glm::vec<2, float, (glm::qualifier)0> &);
    // notifyImageEstimate(ulong);
};