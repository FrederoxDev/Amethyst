#pragma once

template <typename Raw>
struct NewType {
public:
    Raw value;

    constexpr NewType(Raw v) {
        this->value = v;
    }
};