#include "Shape.h"
#include <exception>

Shape::Shape(Color _color) : color(_color) {}

std::vector<double> Shape::Intersects(Ray ray)
{
    throw std::exception("Shape: Unimplemented function - Intersects");
    return { };
}
