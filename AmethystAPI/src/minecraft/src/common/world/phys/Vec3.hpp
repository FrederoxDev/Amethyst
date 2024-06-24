#pragma once
#include <fmt/core.h>
#include <fmt/format.h>

class Vec3 {
public:
    float x;
    float y;
    float z;

public:
    Vec3(float x, float y, float z);

    Vec3 operator+(const Vec3 rhs);
    Vec3 operator-(const Vec3 rhs);
    Vec3 operator*(const Vec3 rhs);
    Vec3 operator/(const Vec3 rhs);
    bool operator==(const Vec3 rhs);

    void rotateAroundXRadians(float angleRadians);
    void rotateAroundYRadians(float angleRadians);
    void rotateAroundZRadians(float angleRadians);
    void rotateAroundPointRadians(const Vec3& pivot, const Vec3& angle);

    void rotateAroundXDegrees(float angleDegrees);
    void rotateAroundYDegrees(float angleDegrees);
    void rotateAroundZDegrees(float angleDegrees);
    void rotateAroundPointDegrees(const Vec3& pivot, const Vec3& angle);
};

// BinaryStream specialization
#include "minecraft/src-deps/core/utility/BinaryStream.hpp"

template <>
Bedrock::Result<Vec3> ReadOnlyBinaryStream::get<Vec3>();

template <>
void BinaryStream::write(Vec3);

template <>
struct fmt::formatter<Vec3> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }

    template <typename FormatContext>
    auto format(const Vec3& pos, FormatContext& ctx)
    {
        return fmt::format_to(ctx.out(), "Vec3(x: {}, y: {}, z: {})", pos.x, pos.y, pos.z);
    }
};