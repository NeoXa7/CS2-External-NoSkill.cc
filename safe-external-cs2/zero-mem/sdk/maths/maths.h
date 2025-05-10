#pragma once
#include "vector.h"

namespace Maths
{
    float DegreeToRadians(const float& degree);
    Vector3 AngleToVector(const Vector3& angle);
    Vector2 CalculateAngles(Vector3& from, Vector3& to);
    Vector3 SmoothAngle(const Vector3& current, const Vector3& target, float smoothFactor);
}