#include "TextureContainer.hpp"
#include <amethyst/Memory.hpp>

bool mce::TextureContainer::isValid() const {
    bool isValid = mStorage.begin() != mStorage.end();
    isValid &= mDescription.mTextureFormat != mce::TextureFormat::UNKNOWN_TEXTURE_FORMAT;

    for (const cg::ImageBuffer& imageBuffer : mStorage) {
        isValid &= imageBuffer.isValid();
    }

    return isValid && mStorage.size() >= mDescription.mMipCount;
}