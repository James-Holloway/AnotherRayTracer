#pragma once
#include <vector>
#include "Ray.h"
#include "Color.h"

struct Shape
{
    Shape(Color _color = CBlack);

    Color color;

    virtual std::vector<double> Intersects(Ray ray);
};

