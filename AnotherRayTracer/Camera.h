#pragma once

#include "Vector3D.h"

struct Camera
{
    Vector3D position;

    Vector3D forward;
    Vector3D right;
    Vector3D up;

    double scale = 0.5;

    void LookAt(Vector3D pos, Vector3D lookAt);
};

