#pragma once
#include <minecraft/src-deps/coregraphics/ImageDescription.hpp>

namespace cg {
    class TextureDescription : public cg::ImageDescription {
    public:
        uint32_t mMipCount;
    };
};