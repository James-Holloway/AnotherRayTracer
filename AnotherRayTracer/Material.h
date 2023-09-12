#pragma once

#include <algorithm>
#include <memory>
#include "Vector3D.h"
#include "Color.h"

struct Light;

constexpr double ART_SPECULAR_EXPONENT = 32;
constexpr double ART_AMBIENT = 0.1;

struct Material
{
    Material(Color _color = CWhite, double _diffuse = 0.5, double _specular = 0.0);

    Color color;
    double diffuse;
    double specular;

    Color GetColor(Vector3D point, Vector3D normal = Vector3D(0, 0, 0), Vector3D viewDir = Vector3D(0, 0, 0), Light* light = nullptr);
};

