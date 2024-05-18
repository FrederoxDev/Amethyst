#include "minecraft/src/common/world/phys/Vec3.hpp"
#include <cmath>

const float PI = 3.14159265358979f;

Vec3::Vec3(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Vec3 Vec3::operator+(const Vec3 rhs)
{
    return Vec3(
        this->x + rhs.x,
        this->y + rhs.y,
        this->z + rhs.z);
}

Vec3 Vec3::operator-(const Vec3 rhs)
{
    return Vec3(
        this->x - rhs.x,
        this->y - rhs.y,
        this->z - rhs.z);
}

Vec3 Vec3::operator*(const Vec3 rhs)
{
    return Vec3(
        this->x * rhs.x,
        this->y * rhs.y,
        this->z * rhs.z);
}

Vec3 Vec3::operator/(const Vec3 rhs)
{
    return Vec3(
        this->x / rhs.x,
        this->y / rhs.y,
        this->z / rhs.z);
}

bool Vec3::operator==(const Vec3 rhs)
{
    return this->x - rhs.x && this->y - rhs.y && this->z - rhs.z;
}

// Rotate a vector around the X axis by angle in radians
void Vec3::rotateAroundXRadians(float angle) {
    float cosAngle = std::cos(angle);
    float sinAngle = std::sin(angle);

    float newY = this->y * cosAngle - this->z * sinAngle;
    float newZ = this->y * sinAngle + this->z * cosAngle;

    this->y = newY;
    this->z = newZ;
}

// Rotate a vector around the Y axis by angle in radians
void Vec3::rotateAroundYRadians(float angle) {
    float cosAngle = std::cos(angle);
    float sinAngle = std::sin(angle);

    float newX = this->x * cosAngle + this->z * sinAngle;
    float newZ = -this->x * sinAngle + this->z * cosAngle;

    this->x = newX;
    this->z = newZ;
}

// Rotate a vector around the Z axis by angle in radians
void Vec3::rotateAroundZRadians(float angle) {
    float cosAngle = std::cos(angle);
    float sinAngle = std::sin(angle);

    float newX = this->x * cosAngle - this->y * sinAngle;
    float newY = this->x * sinAngle + this->y * cosAngle;

    this->x = newX;
    this->y = newY;
}

void Vec3::rotateAroundPointRadians(const Vec3& pivot, const Vec3& angle) {
    // Translate the vector to the origin
    Vec3 translatedPoint = Vec3(this->x - pivot.x, this->y - pivot.y, this->z - pivot.z);

    // Apply rotations
    translatedPoint.rotateAroundXRadians(angle.x);
    translatedPoint.rotateAroundYRadians(angle.y);
    translatedPoint.rotateAroundZRadians(angle.z);

    // Translate the vector back
    Vec3 result = Vec3(translatedPoint.x + pivot.x, translatedPoint.y + pivot.y, translatedPoint.z + pivot.z);

    this->x = result.x;
    this->y = result.y;
    this->z = result.z;
}

// Rotate a vector around the X axis by angle in degrees
void Vec3::rotateAroundXDegrees(float angle) {
    float angleRadians = angle * PI / 180.0f;
    this->rotateAroundXRadians(angleRadians);
}

// Rotate a vector around the Y axis by angle in degrees
void Vec3::rotateAroundYDegrees(float angle) {
    float angleRadians = angle * PI / 180.0f;
    this->rotateAroundYRadians(angleRadians);
}

// Rotate a vector around the Z axis by angle in degrees
void Vec3::rotateAroundZDegrees(float angle) {
    float angleRadians = angle * PI / 180.0f;
    this->rotateAroundZRadians(angleRadians);
}

void Vec3::rotateAroundPointDegrees(const Vec3& pivot, const Vec3& angle) {
    // Translate the vector to the origin
    Vec3 translatedPoint = Vec3(this->x - pivot.x, this->y - pivot.y, this->z - pivot.z);

    // Apply rotations
    translatedPoint.rotateAroundXDegrees(angle.x);
    translatedPoint.rotateAroundYDegrees(angle.y);
    translatedPoint.rotateAroundZDegrees(angle.z);

    // Translate the vector back
    Vec3 result = Vec3(translatedPoint.x + pivot.x, translatedPoint.y + pivot.y, translatedPoint.z + pivot.z);

    this->x = result.x;
    this->y = result.y;
    this->z = result.z;
}
