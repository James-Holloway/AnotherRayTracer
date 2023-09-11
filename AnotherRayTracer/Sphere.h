#pragma once
#include <vector>
#include "Shape.h"

struct Sphere : public Shape
{
    Sphere(Vector3D _center, double _radius, Color _color = CBlack);

    Vector3D center;
    double radius;

    virtual std::vector<double> Intersects(Ray ray) override;
};

