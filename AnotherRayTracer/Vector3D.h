#pragma once
#include <cmath>

struct Vector3D
{
    Vector3D(double x = 0, double y = 0, double z = 0);

    double x;
    double y;
    double z;

    Vector3D operator+ (Vector3D other) const;
    Vector3D operator- (Vector3D other) const;
    Vector3D operator* (Vector3D other) const;
    Vector3D operator* (double scalar) const;
    Vector3D operator/ (Vector3D other) const;
    Vector3D operator/ (double scalar) const;

    double Length() const;
    double LengthSquared() const;

    double Dot(Vector3D other) const;
    Vector3D Cross(Vector3D other) const;

    Vector3D Inverted() const;
    void Invert();

    Vector3D Normalized() const;
    void Normalize();
};

const Vector3D VUnitX = Vector3D(1, 0, 0);
const Vector3D VUnitY = Vector3D(0, 1, 0);
const Vector3D VUnitZ = Vector3D(0, 0, 1);
const Vector3D VZero = Vector3D(0, 0, 0);
const Vector3D VOne = Vector3D(1, 1, 1);