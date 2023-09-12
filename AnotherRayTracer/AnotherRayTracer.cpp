#include "AnotherRayTracer.h"

void AnotherRayTracer::Resize(unsigned int width, unsigned int height)
{
    scene.width = width;
    scene.height = height;
}

void AnotherRayTracer::Render()
{
    image = scene.TraceScene();
}

void AnotherRayTracer::Reset()
{
    scene.Reset();
}

void AnotherRayTracer::PopulateExample()
{
    Reset();
    scene.background = CCornflowerBlue;
    scene.camera.LookAt(Vector3D(0, 2, -8), Vector3D(0, 0, 0));
    
    scene.shapes.push_back(std::make_shared<Sphere>(Vector3D(-2, 0, 2), 1.0, Color(1, 0, 0)));
    scene.shapes.push_back(std::make_shared<Sphere>(Vector3D(0, 0, 0), 1.0, Color(0, 1, 0)));
    scene.shapes.push_back(std::make_shared<Sphere>(Vector3D(2, 0, 2), 1.0, Color(0, 0, 1)));

    scene.lights.push_back(std::make_shared<Light>(Vector3D(5, 10, -5), CWhite));
}

std::string AnotherRayTracer::Parse(std::string input)
{
    ARTParser::ParsedData data = ARTParser::ParseScene(input, scene);

    std::string out = "";
    if (data.errors.size() == 0)
    {
        out = "No errors! :)";
    }
    else
    {
        for (std::string error : data.errors)
        {
            out += error + "\n";
        }
    }
    return out;
}

int AnotherRayTracer::GetWidth()
{
    return scene.width;
}

int AnotherRayTracer::GetHeight()
{
    return scene.height;
}
