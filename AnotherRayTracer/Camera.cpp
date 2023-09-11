#include "Camera.h"

void Camera::LookAt(Vector3D pos, Vector3D lookAt)
{
    position = pos;

    forward = (lookAt - pos).Normalized();
    right = VUnitY.Cross(forward).Normalized();
    up = right.Cross(forward).Inverted().Normalized();
}