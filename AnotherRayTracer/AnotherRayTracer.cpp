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

void AnotherRayTracer::PopulateExample()
{
    scene.camera.LookAt(Vector3D(0, 2, -8), Vector3D(0, 0, 0));
    scene.shapes.clear();
    
    scene.shapes.push_back(std::make_shared<Sphere>(Vector3D(-2, 0, 2), 1.0, Color(1, 0, 0)));
    scene.shapes.push_back(std::make_shared<Sphere>(Vector3D(0, 0, 0), 1.0, Color(0, 1, 0)));
    scene.shapes.push_back(std::make_shared<Sphere>(Vector3D(2, 0, 2), 1.0, Color(0, 0, 1)));
}