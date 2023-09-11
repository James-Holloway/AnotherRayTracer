#include "Ray.h"

Ray::Ray(Vector3D _start, Vector3D _direction) : start(_start), direction(_direction.Normalized()) {}

Vector3D Ray::GetPointFromDistance(double distance)
{
    return start + (direction * distance);
}
