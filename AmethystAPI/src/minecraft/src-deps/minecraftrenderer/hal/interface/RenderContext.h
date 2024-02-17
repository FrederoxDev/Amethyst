#pragma once
#include <cstddef>

namespace mce {
    class RenderContext {
        // I don't know the size!
        std::byte padding0[8];
    };
}