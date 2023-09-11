#include "Material.h"

Material::Material(Color _color) : color(_color) {}

Color Material::GetColor(Vector3D point)
{
    return color;
}
