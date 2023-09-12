#pragma once
#include <memory>
#include <vector>
#include "Ray.h"
#include "Color.h"
#include "Material.h"
#include "Light.h"

struct Scene;

struct Shape
{
    Shape(Color _color = CBlack);
    Shape(Material _material);

    Material material;

    virtual std::vector<double> Intersects(Ray ray);
    virtual Vector3D GetNormal(Vector3D point);
    virtual Color GetColor(Vector3D point, Scene* scene);
};

