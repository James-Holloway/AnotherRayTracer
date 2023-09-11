#include "Sphere.h"

Sphere::Sphere(Vector3D _center, double _radius, Color _color) : center(_center), radius(_radius), Shape(_color) {}

std::vector<double> Sphere::Intersects(Ray ray)
{
    // Offset - the position of the sphere relative to the start of the ray
    Vector3D offset = ray.start - center;

    double b = 2.0 * offset.Dot(ray.direction);
    double c = offset.LengthSquared() - (radius * radius);

    double discriminant = b * b - 4 * c;

    // Ray never intersects spehre - zero intersections
    if (discriminant < 0)
        return { };
    // Ray touches surface of the sphere - one intersection
    if (discriminant == 0)
        return { -b / 2.0 };

    // Otherwise one in, one out - two intersections
    double root = sqrt(discriminant);
    return { (-b - root) / 2.0, (-b + root) / 2.0 };
}

Vector3D Sphere::GetNormal(Vector3D point)
{
    return (point - center).Normalized();
}
