#pragma once

namespace mce {
class Color {
public:
    float r;
    float g;
    float b;
    float a;

    Color(float r, float g, float b, float a)
    {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }

    Color()
    {
        this->r = 0.0f;
        this->g = 0.0f;
        this->b = 0.0f;
        this->a = 0.0f;
    }

    static const Color WHITE;
};
}; // namespace mce