#pragma once

namespace mce {
    class RenderMaterialGroupBase;

    class RenderMaterialGroup {
    public:
        // 1.20.51.1 - 0x572BBB0
        // Found in ItemInHandRenderer::initMaterials
        static RenderMaterialGroupBase* switchable;
    };
};