#pragma once
#include "minecraft/src-client/common/client/gui/controls/UIComponent.hpp"
#include <cstddef>
#include <cstdint>
#include <string>
#include <amethyst/Memory.hpp>

class TextComponent : public UIComponent {
public:
    /* this + 16  */ std::byte padding16[288];
    /* this + 304 */ std::string mLabel;

    // 1.20.71.1 - 48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8D B9 ? ? ? ? 48 8B DA 48 83 7F
    void setText(const std::string& text);
};

///* this + 464 */ bool mCachedTextDirty;