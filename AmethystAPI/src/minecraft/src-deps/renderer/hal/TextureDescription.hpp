#pragma once
#include <minecraft/src-deps/coregraphics/TextureDescription.hpp>
#include <minecraft/src-deps/core/math/Color.hpp>

namespace mce {
    class TextureDescription : public cg::TextureDescription {
    public:
        short something;
        mce::Color mClearColor;
        float mOptimisedClearDepth;
        short e;
        short j;
        std::byte test[100];
    };
}