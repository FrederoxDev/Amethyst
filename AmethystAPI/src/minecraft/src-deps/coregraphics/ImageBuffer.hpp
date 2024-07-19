#pragma once
#include <minecraft/src-deps/coregraphics/ImageDescription.hpp>
#include <minecraft/src-deps/core/container/Blob.hpp>
#include <amethyst/Log.hpp>

namespace cg {
    class ImageBuffer {
    public:
        mce::Blob mStorage;
        cg::ImageDescription mImageDescription;

        ImageBuffer(mce::Blob&& blob, cg::ImageDescription&& imageDescription)
            : mStorage(std::move(blob)), mImageDescription(std::move(imageDescription)) {}

        ImageBuffer(const ImageBuffer& other)
            : mStorage(other.mStorage), mImageDescription(other.mImageDescription) {}

        __declspec(noinline) bool isValid() const {
            size_t blobSize = mStorage.size();
            mce::TextureFormat format = mImageDescription.mTextureFormat;

            if ((unsigned int)format - 117 > 0x1B) {
                int v6 = 0;

                if (mImageDescription.mWidth != 0 && mImageDescription.mHeight != 0) {
                    v6 = mImageDescription.mWidth * mImageDescription.mHeight * cg::ImageDescription::getStrideFromFormat(format);
                }

                int v8 = 6;
                if (mImageDescription.mImageType != cg::ImageType::Cubemap) {
                    v8 = mImageDescription.mArraySize;
                }

                return blobSize == v6 * v8;
            }

            Assert("checking not implemented for compressed images");
        }
    };
};