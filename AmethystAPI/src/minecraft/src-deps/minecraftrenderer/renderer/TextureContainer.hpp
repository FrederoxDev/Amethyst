#pragma once
#include <cstddef>
#include <minecraft/src-deps/coregraphics/ImageBuffer.hpp>

namespace mce {
    class TextureContainer {
    public:
        std::byte padding0[88];

        // 1.21.0.3 - 48 8B C4 48 89 48 ? 53 48 83 EC ? 48 8B D9 33 C9 48 89 0B
        TextureContainer(cg::ImageBuffer&&);
    };
}