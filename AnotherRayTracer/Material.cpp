#include "Material.h"
#include "Light.h"
#include "Scene.h"

Material::Material(Color _color, double _diffuse, double _specular, double _reflective) : color(_color), diffuse(_diffuse), specular(_specular), reflective(_reflective) {}

Color Material::GetColor(Vector3D point, Vector3D normal, Ray ray, Light* light)
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
        Vector3D halfwayDir = (lightDir + ray.direction.Inverted()).Normalized();
        double spec = pow(std::max<double>(0.0, normal.Dot(halfwayDir)), ART_SPECULAR_EXPONENT) * specular;
        lighting = lighting + (Color(spec, spec, spec));
    }

    return color * lighting;
}

// Reflects and traces a new ray
Color Material::Reflect(Vector3D point, Vector3D reflex, Scene* scene, unsigned int depth)
{
    if (scene == nullptr || depth > scene->maxBounces)
    {
        return Color(0, 0, 0);
    }
    if (reflective <= 0.0)
    {
        return Color(0, 0, 0);
    }
    Ray reflectRay = Ray(point, reflex);
    Color col = scene->Trace(reflectRay, depth + 1);
    return col * reflective;
}
