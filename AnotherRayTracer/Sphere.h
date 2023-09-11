#pragma once
#include <vector>
#include "Shape.h"

struct Sphere : public Shape
{
    Sphere(Vector3D _center, double _radius, Color _color = CBlack);
    Sphere(Vector3D _center, double _radius, Material _material);

    Vector3D center;
    double radius;

    virtual std::vector<double> Intersects(Ray ray) override;
    virtual Vector3D GetNormal(Vector3D point) override;
};

