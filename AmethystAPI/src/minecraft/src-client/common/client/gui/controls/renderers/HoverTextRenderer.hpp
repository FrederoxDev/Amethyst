#pragma once
#include <minecraft/src-client/common/client/gui/controls/renderers/HoverRenderer.hpp>

class UIResolvedDef;

class HoverTextRenderer : public HoverRenderer {
public:
    // 1.20.71.1 ctor target - 48 89 5C 24 ? 48 89 74 24 ? 48 89 4C 24 ? 57 48 83 EC ? 48 8B F2 48 8B D9 C7 41
    void* _HoverTextRenderer(HoverTextRenderer*, const UIResolvedDef*);
};