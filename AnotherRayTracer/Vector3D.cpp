#include "Vector3D.h"

Vector3D::Vector3D(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}

Vector3D Vector3D::operator+(Vector3D other) const
{
    return Vector3D(x + other.x, y + other.y, z + other.z);
}

Vector3D Vector3D::operator-(Vector3D other) const
{
    return Vector3D(x - other.x, y - other.y, z - other.z);
}

Vector3D Vector3D::operator*(Vector3D other) const
{
    return Vector3D(x * other.x, y * other.y, z * other.z);
}

Vector3D Vector3D::operator*(double scalar) const
{
    return Vector3D(x * scalar, y * scalar, z * scalar);
}

Vector3D Vector3D::operator/(Vector3D other) const
{
    return Vector3D(x / other.x, y / other.y, z / other.z);
}

Vector3D Vector3D::operator/(double scalar) const
{
    return Vector3D(x / scalar, y / scalar, z / scalar);
}

double Vector3D::Length() const
{
    return sqrt(LengthSquared());
}

double Vector3D::LengthSquared() const
{
    return (x * x) + (y * y) + (z * z);
}

double Vector3D::Dot(Vector3D other) const
{
    return (x * other.x) + (y * other.y) + (z * other.z);
}

Vector3D Vector3D::Cross(Vector3D other) const
{
    return Vector3D(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    );
}

Vector3D Vector3D::Inverted() const
{
    return Vector3D(-x, -y, -z);
}

void Vector3D::Invert()
{
    *this = Inverted();
}

Vector3D Vector3D::Normalized() const
{
    return *this / Length();
}

void Vector3D::Normalize()
{
    *this = Normalized();
}
