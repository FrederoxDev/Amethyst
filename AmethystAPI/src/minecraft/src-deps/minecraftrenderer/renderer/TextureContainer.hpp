#pragma once
#include <cstddef>
#include <vector>
#include <minecraft/src-deps/coregraphics/ImageBuffer.hpp>
#include <minecraft/src-deps/renderer/hal/TextureDescription.hpp>

namespace cg { class ImageBuffer; }

namespace mce {
    class TextureContainer {
    public:
        std::vector<cg::ImageBuffer> mStorage;
        mce::TextureDescription mDescription;

        // 1.21.0.3 - 48 8B C4 48 89 48 ? 53 48 83 EC ? 48 8B D9 33 C9 48 89 0B
        TextureContainer(cg::ImageBuffer&&);

        bool isValid() const;
    };
}