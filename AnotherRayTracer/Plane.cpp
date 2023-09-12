#include "Plane.h"

Plane::Plane(Vector3D _normal, double _distance, Color _color) : normal(_normal.Normalized()), distance(_distance), Shape(_color) {}

Plane::Plane(Vector3D _normal, double _distance, Material _material) : normal(_normal.Normalized()), distance(_distance), Shape(_material) {} 

std::vector<double> Plane::Intersects(Ray ray)
{
    double angle = ray.direction.Dot(normal);
    if (angle == 0)
        return {};

    double b = normal.Dot(ray.start - (normal * distance));
    return { -b / angle };
}

Vector3D Plane::GetNormal(Vector3D point)
{
    return normal;
}
