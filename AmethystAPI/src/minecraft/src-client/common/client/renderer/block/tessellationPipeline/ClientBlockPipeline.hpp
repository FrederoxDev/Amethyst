#pragma once
#include <vector>
#include <memory>

namespace ClientBlockPipeline {
    class Step {
        uint64_t mStepId;
    };

    class Description {
    public:
        class BakedStep {};

        std::vector<std::shared_ptr<ClientBlockPipeline::Step>> mSteps;
        std::vector<std::shared_ptr<ClientBlockPipeline::Step>> mOutput;
        std::vector<ClientBlockPipeline::Description::BakedStep> mBakedSteps;
        std::byte padding72[104 - 72];
    };

    class MaterialRepository;
};