#include "Light.h"

Light::Light(Vector3D _position, Color _color) : position(_position), color(_color) {}

Color Light::Illuminate(Material material, Vector3D point, double brightness, Vector3D normal, Ray ray)
{
    return material.GetColor(point, normal, ray, this) * color * brightness;
}
