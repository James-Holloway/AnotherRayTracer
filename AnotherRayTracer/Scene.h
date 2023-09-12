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
#include "Plane.h"

constexpr double ART_THRESHOLD = 0.0001;

struct Scene
{
    Color background = CCornflowerBlue;
    Camera camera{};

    unsigned int maxBounces = 3;

    unsigned int width = 512;
    unsigned int height = 512;

    std::vector<std::shared_ptr<Shape>> shapes{};
    std::vector<std::shared_ptr<Light>> lights{};

    void Reset();

    void Intersections(Ray ray, std::map<double, std::shared_ptr<Shape>>& intersections);

    Color Trace(Ray ray, unsigned int depth = 0);
    Color Trace(unsigned int x, unsigned int y);
    void TraceBatch(std::vector<unsigned char>* image, unsigned int offset, unsigned int batchSize);
    std::vector<unsigned char> TraceScene();
};