#pragma once
#include <cstdint>
#include <variant>

class SomethingWithSize16 {
    uint64_t a;
    uint64_t b;
};

class ItemStackNetIdVariant {
    // std::variant<TypedServerNetId<struct ItemStackNetIdTag, int32_t, 0>, TypedClientNetId<struct ItemStackRequestIdTag, int32_t, 0>, TypedClientNetId<struct ItemStackLegacyRequestIdTag, int32_t, 0>> mVariant;
    std::variant<SomethingWithSize16> mVariant;

public:
    ItemStackNetIdVariant() = default;
};

static_assert(sizeof(ItemStackNetIdVariant) == 24);