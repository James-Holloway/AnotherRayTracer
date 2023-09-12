#pragma once
#include "Shape.h"
struct Plane : public Shape
{
    Plane(Vector3D _normal, double _distance, Color _color = CBlack);
    Plane(Vector3D _normal, double _distance, Material _material);

    Vector3D normal;
    double distance;

    virtual std::vector<double> Intersects(Ray ray) override;
    virtual Vector3D GetNormal(Vector3D point) override;
};

