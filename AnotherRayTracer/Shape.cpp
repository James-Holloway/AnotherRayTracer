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

Color Shape::GetColor(Vector3D point, Scene* scene)
{
    Vector3D normal = GetNormal(point);
    Color color = Color(0, 0, 0);

    // If no lights then fullbright
    if (scene->lights.size() == 0)
    {
        return material.GetColor(point);
    }

    for (std::shared_ptr<Light> light : scene->lights)
    {
        Vector3D v = light->position - point;

        // Shadows
        Ray ray = Ray(point, v);
        std::map<double, std::shared_ptr<Shape>> intersections;
        scene->Intersections(ray, intersections);

        if (intersections.size() > 0)
        {
            // If the ray intersected with an object closer to the light than this, then continue
            if (intersections.begin()->first <= v.Length())
                continue;
        }


        double brightness = normal.Dot(v.Normalized());

        if (brightness <= 0)
            continue;

        Color illuminaton = light->Illuminate(material, point, brightness);
        color = color + illuminaton;
    }

    return color;
}
