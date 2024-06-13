#include <minecraft/src-deps/core/utility/ErrorInfo.hpp>

#include <expected_lite/expected.hpp>

namespace Bedrock {
    template <typename T, typename Err>
    class Result : public nonstd::expected<T, ErrorInfo<Err>> {
        using Base = nonstd::expected<T, ErrorInfo<Err>>;
        using Base::Base;
        std::byte padding24[100];
    };
};