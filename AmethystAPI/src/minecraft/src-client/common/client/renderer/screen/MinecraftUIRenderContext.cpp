#include "common/client/renderer/screen/MinecraftUIRenderContext.h"

float MinecraftUIRenderContext::getLineLength(Font& font, const std::string& text, float fontSize, bool showColorSymbol)
{
    using function = float(__thiscall*)(MinecraftUIRenderContext*, Font&, const std::string&, float, bool);
    return reinterpret_cast<function>(this->vtable[1])(this, font, text, fontSize, showColorSymbol);
}

float MinecraftUIRenderContext::getTextAlpha()
{
    using function = float(__thiscall*)(MinecraftUIRenderContext*);
    return reinterpret_cast<function>(this->vtable[2])(this);
}

void MinecraftUIRenderContext::setTextAlpha(float alpha)
{
    using function = void(__thiscall*)(MinecraftUIRenderContext*, float);
    return reinterpret_cast<function>(this->vtable[3])(this, alpha);
}

void MinecraftUIRenderContext::drawDebugText(const RectangleArea* rect, const std::string* text, const mce::Color* color, float alpha, ui::TextAlignment alignment, const TextMeasureData* textData, const CaretMeasureData* caretData)
{
    using function = void(__thiscall*)(MinecraftUIRenderContext*, const RectangleArea*, const std::string*, const mce::Color*, float, ui::TextAlignment, const TextMeasureData*, const CaretMeasureData*);
    return reinterpret_cast<function>(this->vtable[4])(this, rect, text, color, alpha, alignment, textData, caretData);
}

void MinecraftUIRenderContext::flushText(float deltaTime)
{
    using function = void(__thiscall*)(MinecraftUIRenderContext*, float);
    return reinterpret_cast<function>(this->vtable[6])(this, deltaTime);
}

void MinecraftUIRenderContext::drawImage(const mce::TexturePtr& texture, const glm::tvec2<float>* position, const glm::tvec2<float>* size, glm::tvec2<float>* uv, glm::tvec2<float>* uvSize, int degree)
{
    using function = void(__thiscall*)(MinecraftUIRenderContext*, const mce::TexturePtr&, const glm::tvec2<float>*, const glm::tvec2<float>*, glm::tvec2<float>*, glm::tvec2<float>*, int);
    return reinterpret_cast<function>(this->vtable[7])(this, texture, position, size, uv, uvSize, degree);
}

void MinecraftUIRenderContext::drawNineslice(const mce::TexturePtr* texture, const NinesliceInfo* nineslice) {
    using function = void(__thiscall*)(MinecraftUIRenderContext*, const mce::TexturePtr* texture, const NinesliceInfo* nineslice);
    return reinterpret_cast<function>(this->vtable[8])(this, texture, nineslice);
}

void MinecraftUIRenderContext::flushImages(const mce::Color& color, float alpha, const HashedString& materialNameHash)
{
    using function = void(__thiscall*)(MinecraftUIRenderContext*, const mce::Color&, float, const HashedString&);
    return reinterpret_cast<function>(this->vtable[9])(this, color, alpha, materialNameHash);
}

void MinecraftUIRenderContext::drawRectangle(const RectangleArea* rect, const mce::Color* color, float alpha, int thickness)
{
    using function = void(__thiscall*)(MinecraftUIRenderContext*, const RectangleArea*, const mce::Color*, float, int);
    return reinterpret_cast<function>(this->vtable[13])(this, rect, color, alpha, thickness);
}

void MinecraftUIRenderContext::fillRectangle(const RectangleArea* rect, const mce::Color* color, float alpha)
{
    using function = void(__thiscall*)(MinecraftUIRenderContext*, const RectangleArea*, const mce::Color*, float);
    return reinterpret_cast<function>(this->vtable[14])(this, rect, color, alpha);
}

mce::TexturePtr* MinecraftUIRenderContext::getTexture(mce::TexturePtr* result, const ResourceLocation* resourceLocation, bool forceReload)
{
    using function = mce::TexturePtr*(__thiscall*)(MinecraftUIRenderContext*, mce::TexturePtr*, const ResourceLocation*, bool);
    return reinterpret_cast<function>(this->vtable[29])(this, result, resourceLocation, forceReload);
}