#pragma once
#include "minecraft/src/common/world/phys/Vec2.hpp"
#include "minecraft/src-client/common/client/renderer/screen/MinecraftUIRenderContext.hpp"
#include "glm/glm.hpp"

namespace Amethyst {
    struct TextureUV {
        glm::tvec2<float> uvPos;
        glm::tvec2<float> uvSize;
        float width;
        float height;
    };

    class NinesliceHelper {
    public:
        NinesliceHelper(int textureWidth, int textureHeight, int ninesliceWidth, int nicesliceHeight);
        void Draw(RectangleArea& rect, const mce::TexturePtr* texture, MinecraftUIRenderContext* ctx);

    private: 
        TextureUV Slice(int x, int y, int xSize, int ySize) const;
        ImageInfo Scale(TextureUV* slice, float x, float y, float xSize, float ySize);

    private:
        float mTextureWidth;
        float mTextureHeight;
        float mNinesliceWidth;
        float mNinesliceHeight;
        TextureUV mSlices[9];
    };
} // namespace Amethyst