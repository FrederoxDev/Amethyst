#include "common/world/phys/Vec3.h"

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