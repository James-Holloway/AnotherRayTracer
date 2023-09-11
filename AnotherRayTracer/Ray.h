#pragma once
#include "Vector3D.h"

struct Ray
{
    Ray(Vector3D start, Vector3D direction);

    Vector3D start;
    Vector3D direction;
};

