#include "Material.h"
#include "Light.h"

Material::Material(Color _color, double _diffuse, double _specular) : color(_color), diffuse(_diffuse), specular(_specular) {}

Color Material::GetColor(Vector3D point, Vector3D normal, Vector3D viewDir, Light* light)
{
    if (light == nullptr)
        return color;

    Color lighting = Color(0, 0, 0);
    Vector3D lightDir = (light->position - point).Normalized();

    if (diffuse > 0.0)
    {
        double diff = std::max<double>(0.0, normal.Dot(lightDir)) * diffuse;
        lighting = lighting + Color(diff, diff, diff);
    }

    if (specular > 0.0)
    {
        Vector3D halfwayDir = (lightDir + viewDir).Normalized();
        double spec = pow(std::max<double>(0.0, normal.Dot(halfwayDir)), ART_SPECULAR_EXPONENT);
        lighting = lighting + Color(spec, spec, spec);
    }

    return color * lighting;
}
