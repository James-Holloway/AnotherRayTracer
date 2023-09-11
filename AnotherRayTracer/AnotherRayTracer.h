#pragma once
#include "Scene.h"

class AnotherRayTracer
{
public:
    Scene scene;
    std::vector<unsigned char> image{};
    void Resize(unsigned int width, unsigned int height);
    void Render();
    void PopulateExample();
};

