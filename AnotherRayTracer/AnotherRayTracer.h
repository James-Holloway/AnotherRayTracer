#pragma once
#include "Scene.h"
#include "ARTParser.h"

class AnotherRayTracer
{
public:
    Scene scene;
    std::vector<unsigned char> image{};
    void Resize(unsigned int width, unsigned int height);
    void Render();
    void Reset();
    void PopulateExample();
    std::string Parse(std::string input);

    static inline char NewScene[] = "# Background\n"
        "color cornflowerblue 100 149 237\n"
        "background cornflowerblue\n"
        "# Camera\n"
        "camera 0 2 -8 0 0 0\n"
        "# Colors & Materials\n"
        "color white 255 255 255\n"
        "color red 255 0 0\n"
        "color green 0 255 0\n"
        "color blue 0 0 255\n"
        "material red red\n"
        "material green green\n"
        "material blue blue\n"
        "# Spheres\n"
        "sphere -2 0 2 1.0 red\n"
        "sphere 0 0 0 1.0 green\n"
        "sphere 2 0 2 1.0 blue\n"
        "# Lights\n"
        "light 5 10 -5 white\n";
};