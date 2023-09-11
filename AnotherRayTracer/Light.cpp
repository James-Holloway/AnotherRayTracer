#include "Light.h"

Light::Light(Vector3D _position, Color _color) : position(_position), color(_color) {}

Color Light::Illuminate(Material material, Vector3D point, double brightness)
{
    return material.GetColor(point) * color * brightness;
}
