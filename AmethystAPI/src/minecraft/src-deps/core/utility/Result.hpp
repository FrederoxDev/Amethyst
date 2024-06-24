#pragma once
#include <minecraft/src-deps/core/utility/ErrorInfo.hpp>
#include <expected_lite/expected.hpp>
#include <type_traits>

struct success_t {};
constexpr success_t success{};

namespace Bedrock {
    template <typename T, typename Err = std::error_code>
    class Result : public nonstd::expected_lite::expected<T, ErrorInfo<Err>> {
        using Base = nonstd::expected_lite::expected<T, ErrorInfo<Err>>;
        using Base::Base;
    };

    template <typename Err>
    class Result<void, Err> : public nonstd::expected_lite::expected<success_t, ErrorInfo<Err>> {
        using Base = nonstd::expected_lite::expected<success_t, ErrorInfo<Err>>;
        using Base::Base;
    };
}; // namespace Bedrock