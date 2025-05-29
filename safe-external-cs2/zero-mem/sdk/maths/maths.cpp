#include <pch.h>
#include "maths.h"

namespace Maths
{
    float DegreeToRadians(const float& degree) {
        return (degree)*M_PI / 180;
    }

    float RadianToDegrees(const float& degree) {
        return (degree)*180 / M_PI;
    }

    Vector3 AngleToVector(const Vector3& angle) {
        float pitch = angle.x;
        float yaw = angle.y;

        float pitch_radians = Maths::DegreeToRadians(pitch);
        float yaw_radians = Maths::DegreeToRadians(yaw);

        float sin_pitch = sinf(pitch_radians);
        float cos_pitch = cosf(pitch_radians);
        float sin_yaw = sinf(yaw_radians);
        float cos_yaw = cosf(yaw_radians);

        return Vector3(cos_pitch * cos_yaw, cos_pitch * sin_yaw, -sin_pitch);
    }

    Vector2 CalculateAngles(Vector3& from, Vector3& to) {
        float yaw, pitch;
        float dx = to.x - from.x;
        float dy = to.y - from.y;
        float dz = to.z - from.z;
        double distance = sqrt(pow(dx, 2) + pow(dy, 2));

        yaw = static_cast<float>(Maths::RadianToDegrees(atan2(dy, dx)));
        pitch = -static_cast<float>(Maths::RadianToDegrees(atan2(dz, distance)));

        return Vector2(yaw, pitch);
    }

    Vector3 SmoothAngle(const Vector3& current, const Vector3& target, float smoothFactor) {
        Vector3 delta = target - current;

        // Normalize angles if needed
        delta.x = std::fmodf(delta.x + 180.0f, 360.0f) - 180.0f;
        delta.y = std::fmodf(delta.y + 180.0f, 360.0f) - 180.0f;

        return current + (delta / smoothFactor);
    }
}