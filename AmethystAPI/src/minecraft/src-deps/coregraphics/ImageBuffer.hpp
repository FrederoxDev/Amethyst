#pragma once
#include <minecraft/src-deps/coregraphics/ImageDescription.hpp>
#include <minecraft/src-deps/core/container/Blob.hpp>

namespace cg {
    class ImageBuffer {
    public:
        mce::Blob mStorage;
        cg::ImageDescription mImageDescription;

        ImageBuffer(mce::Blob&& blob, cg::ImageDescription&& imageDescription)
            : mStorage(std::move(blob)), mImageDescription(std::move(imageDescription)) {}
    };
};