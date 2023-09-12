#include "Shape.h"
#include <exception>
#include "Scene.h"

Shape::Shape(Color _color) : material(_color) {}

Shape::Shape(Material _material) : material(_material) {}

std::vector<double> Shape::Intersects(Ray ray)
{
    throw std::exception("Shape: Unimplemented function - Intersects");
    return { };
}

Vector3D Shape::GetNormal(Vector3D point)
{
    throw std::exception("Shape: Unimplemented function - GetNormal");
    return {};
}

Color Shape::GetColor(Vector3D point, Ray ray, Scene* scene)
{
    // If no lights then fullbright
    if (scene->lights.size() == 0)
    {
        return material.GetColor(point);
    }

    Vector3D normal = GetNormal(point);
    Color color = Color(0, 0, 0);
    Vector3D reflex = ray.Reflect(normal);

    Vector3D viewDir = ray.direction.Inverted();

    for (std::shared_ptr<Light> light : scene->lights)
    {
        Vector3D v = light->position - point;

        // Shadows
        Ray ray = Ray(point, v);
        std::map<double, std::shared_ptr<Shape>> intersections;
        scene->Intersections(ray, intersections);

        if (intersections.size() > 0)
        {
            // If the ray intersected with an object closer to the light than this, then don't illuminate with this light
            if (intersections.begin()->first <= v.Length())
                continue;
        }

        double brightness = normal.Dot(v.Normalized());

        if (brightness <= 0)
            continue;

        Color illuminaton = light->Illuminate(material, point, brightness, normal, viewDir);
        color = color + illuminaton;
    }

    color = color + (material.color * ART_AMBIENT);

    return color;
}
