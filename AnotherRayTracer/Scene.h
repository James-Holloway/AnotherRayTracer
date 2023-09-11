#pragma once

#include <vector>
#include <map>
#include <memory>
#include <thread>
#include "Vector3D.h"
#include "Ray.h"
#include "Camera.h"
#include "Color.h"
#include "Shape.h"
#include "Sphere.h"
#include "Light.h"

struct Scene
{
    Color background{ 0.392f, 0.584f, 0.929 }; // Cornflower blue
    Camera camera{};

    unsigned int width = 512;
    unsigned int height = 512;

    std::vector<std::shared_ptr<Shape>> shapes{};
    std::vector<std::shared_ptr<Light>> lights{};

    Color Trace(unsigned int x, unsigned int y);
    void TraceBatch(std::vector<unsigned char>* image, unsigned int offset, unsigned int batchSize);
    std::vector<unsigned char> TraceScene();
};