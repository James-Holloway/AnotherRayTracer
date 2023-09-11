#pragma once

#include "Vector3D.h"
#include "Color.h"

struct Material
{
    Material(Color _color = CWhite);

    Color color;

    Color GetColor(Vector3D point);
};

