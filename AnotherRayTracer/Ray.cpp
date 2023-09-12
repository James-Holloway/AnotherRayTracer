#include "Ray.h"

Ray::Ray(Vector3D _start, Vector3D _direction) : start(_start), direction(_direction.Normalized()) {}

Vector3D Ray::GetPointFromDistance(double distance)
{
    return start + (direction * distance);
}

Vector3D Ray::Reflect(Vector3D normal)
{
    Vector3D inverse = direction.Inverted();
    return inverse + (((normal * normal.Dot(inverse)) + direction) * 2.0);
}
