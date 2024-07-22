#pragma once
#include <memory>
#include <minecraft/src-deps/core/utility/AutomaticID.hpp>
#include <minecraft/src-client/common/client/renderer/block/tessellationPipeline/ClientBlockPipeline.hpp>

class BaseLightTextureImageBuilder;

enum BakedBlockLightType : int32_t {
    None,
    Flat,
    Smooth
};

class VanillaBlockTessellation {
public:
    // 1.21.0.3 - 48 89 5C 24 ? 57 48 83 EC ? 66 C7 41
    static std::unique_ptr<ClientBlockPipeline::Description> createWorldPipelineDescription(
        std::shared_ptr<ClientBlockPipeline::MaterialRepository>,
        const DimensionType&,
        BakedBlockLightType,
        BaseLightTextureImageBuilder*
    );
};