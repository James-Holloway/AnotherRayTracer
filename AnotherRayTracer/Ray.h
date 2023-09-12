#pragma once
#include "Vector3D.h"

struct Ray
{
    Ray(Vector3D start, Vector3D direction);

    Vector3D start;
    Vector3D direction;

    Vector3D GetPointFromDistance(double distance);
    Vector3D Reflect(Vector3D normal);
};
