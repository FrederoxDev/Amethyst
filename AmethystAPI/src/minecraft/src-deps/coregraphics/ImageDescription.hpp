#pragma once
#include <cstdint>
#include <minecraft/src-deps/coregraphics/enums/ColorSpace.hpp>
#include <minecraft/src-deps/coregraphics/enums/TextureFormat.hpp>

namespace cg {
    struct ImageDescription {
        uint32_t mWidth;
        uint32_t mHeight;
        mce::TextureFormat mTextureFormat;
        cg::ColorSpace mColorSpace;
        bool mIsCubemap;
        uint32_t mArraySize;

        ImageDescription(uint32_t width, uint32_t height, mce::TextureFormat format, cg::ColorSpace colorSpace, bool isCubemap, uint32_t arraySize) 
            : mWidth(width), mHeight(height), mTextureFormat(format), mColorSpace(colorSpace), mIsCubemap(isCubemap), mArraySize(arraySize) {}
    };
};