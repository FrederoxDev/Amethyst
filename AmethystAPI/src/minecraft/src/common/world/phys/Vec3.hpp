#pragma once

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