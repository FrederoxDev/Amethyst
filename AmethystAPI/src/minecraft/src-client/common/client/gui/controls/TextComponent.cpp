#include "minecraft/src-client/common/client/gui/controls/TextComponent.hpp"

void TextComponent::setText(const std::string& text) {
    using function = decltype(&TextComponent::setText);
    static auto func = std::bit_cast<function>(SigScan("48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8D B9 ? ? ? ? 48 8B DA 48 83 7F"));
    (this->*func)(text);
}