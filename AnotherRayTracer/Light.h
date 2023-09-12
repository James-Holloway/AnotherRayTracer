#pragma once

#include <memory>
#include "Vector3D.h"
#include "Material.h"
#include "Color.h"
#include "Ray.h"

struct Light
{
    Light(Vector3D _position, Color _color);

    Vector3D position;
    Color color;

    Color Illuminate(Material material, Vector3D point, double brightness, Vector3D normal, Ray ray);
};

