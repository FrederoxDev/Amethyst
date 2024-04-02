#include "amethyst/ui/NinesliceHelper.hpp"

Amethyst::NinesliceHelper::NinesliceHelper(int textureWidth, int textureHeight, int ninesliceWidth, int ninesliceHeight)
{
    mTextureWidth = (float)textureWidth;
    mTextureHeight = (float)textureHeight;
    mNinesliceWidth = (float)ninesliceWidth;
    mNinesliceHeight = (float)ninesliceHeight;

    int middleWidth = textureWidth - ninesliceWidth * 2;
    int middleHeight = textureHeight - ninesliceHeight * 2;

    mSlices[0] = Slice(0, 0, ninesliceWidth, ninesliceHeight);                             // Top Left
    mSlices[1] = Slice(ninesliceWidth, 0, middleWidth, ninesliceHeight);                   // Top Middle
    mSlices[2] = Slice(textureWidth - ninesliceWidth, 0, ninesliceWidth, ninesliceHeight); // Top Right

    mSlices[3] = Slice(0, ninesliceHeight, ninesliceWidth, middleHeight);                             // Middle Left
    mSlices[4] = Slice(ninesliceWidth, ninesliceHeight, middleWidth, middleHeight);                   // Middle Middle
    mSlices[5] = Slice(textureWidth - ninesliceWidth, ninesliceHeight, ninesliceWidth, middleHeight); // Middle Right

    mSlices[6] = Slice(0, textureHeight - ninesliceHeight, ninesliceWidth, ninesliceHeight);                             // Bottom Left
    mSlices[7] = Slice(ninesliceWidth, textureHeight - ninesliceHeight, middleWidth, ninesliceHeight);                   // Bottom Middle
    mSlices[8] = Slice(textureWidth - ninesliceWidth, textureHeight - ninesliceHeight, ninesliceWidth, ninesliceHeight); // Bottom Right
}

Amethyst::TextureUV Amethyst::NinesliceHelper::Slice(int x, int y, int xSize, int ySize) const
{
    glm::tvec2<float> uvPos((float)x / mTextureWidth, (float)y / mTextureHeight);
    glm::tvec2<float> uvSize((float)xSize / mTextureWidth, (float)ySize / mTextureHeight);
    return {uvPos, uvSize, (float)xSize, (float)ySize};
}

ImageInfo Amethyst::NinesliceHelper::Scale(TextureUV* slice, float x, float y, float xSize, float ySize)
{
    glm::tvec2<float> size(xSize, ySize);
    glm::tvec2<float> position(x, y);
    return {position, size, slice->uvPos, slice->uvSize};
}

void Amethyst::NinesliceHelper::Draw(RectangleArea& rect, const mce::TexturePtr* texture, MinecraftUIRenderContext* ctx)
{
    float xOff = rect._x0;
    float yOff = rect._y0;

    float width = rect._x1 - rect._x0;
    float height = rect._y1 - rect._y0;

    float middleWidth = width - 2 * mNinesliceWidth;
    float middleHeight = height - 2 * mNinesliceHeight;

    ImageInfo topLeft = Scale(&mSlices[0], xOff, yOff, mNinesliceWidth, mNinesliceHeight);
    ImageInfo top = Scale(&mSlices[1], xOff + mNinesliceWidth, yOff, middleWidth, mNinesliceHeight);
    ImageInfo topRight = Scale(&mSlices[2], xOff + width - mNinesliceWidth, yOff, mNinesliceWidth, mNinesliceHeight);
    ImageInfo left = Scale(&mSlices[3], xOff, yOff + mNinesliceHeight, mNinesliceWidth, middleHeight);
    ImageInfo middle = Scale(&mSlices[4], xOff + mNinesliceWidth, yOff + mNinesliceHeight, middleWidth, middleHeight);
    ImageInfo right = Scale(&mSlices[5], xOff + width - mNinesliceWidth, yOff + mNinesliceHeight, mNinesliceWidth, middleHeight);
    ImageInfo bottomLeft = Scale(&mSlices[6], xOff, yOff + height - mNinesliceHeight, mNinesliceWidth, mNinesliceHeight);
    ImageInfo bottom = Scale(&mSlices[7], xOff + mNinesliceWidth, yOff + height - mNinesliceHeight, middleWidth, mNinesliceHeight);
    ImageInfo bottomRight = Scale(&mSlices[8], xOff + width - mNinesliceWidth, yOff + height - mNinesliceHeight, mNinesliceWidth, mNinesliceHeight);

    glm::tvec2<float> uvScale(1.0f, 1.0f);

    NinesliceInfo nineSlice = {
        topLeft,
        topRight,
        bottomLeft,
        bottomRight,
        uvScale,
        {left},
        {top},
        {bottom},
        {right},
        {middle}};

    ctx->drawNineslice(texture, &nineSlice);
}