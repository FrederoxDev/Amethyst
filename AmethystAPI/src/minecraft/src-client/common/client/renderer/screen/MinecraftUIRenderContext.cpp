#include "minecraft/src-client/common/client/renderer/screen/MinecraftUIRenderContext.h"

float MinecraftUIRenderContext::getLineLength(Font& font, const std::string& text, float fontSize, bool showColorSymbol) {
	using function = float(__thiscall*)(MinecraftUIRenderContext*, Font&, const std::string&, float, bool);
	return reinterpret_cast<function>(this->vtable[1])(this, font, text, fontSize, showColorSymbol);
}

float MinecraftUIRenderContext::getTextAlpha() {
	using function = float(__thiscall*)(MinecraftUIRenderContext*);
	return reinterpret_cast<function>(this->vtable[2])(this);
}

void MinecraftUIRenderContext::setTextAlpha(float alpha) {
	using function = void(__thiscall*)(MinecraftUIRenderContext*, float);
	return reinterpret_cast<function>(this->vtable[3])(this, alpha);
}

void MinecraftUIRenderContext::drawDebugText(const RectangleArea* rect, const std::string* text, const mce::Color* color, float alpha, ui::TextAlignment alignment, const TextMeasureData* textData, const CaretMeasureData* caretData) {
	using function = void(__thiscall*)(MinecraftUIRenderContext*, const RectangleArea*, const std::string*, const mce::Color*, float, ui::TextAlignment, const TextMeasureData*, const CaretMeasureData*);
	return reinterpret_cast<function>(this->vtable[4])(this, rect, text, color, alpha, alignment, textData, caretData);
}