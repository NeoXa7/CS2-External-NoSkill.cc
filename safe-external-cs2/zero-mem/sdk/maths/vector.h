#pragma once
#include <globals/defs.h>
#include <globals/imports.h>
#include "matrix.h"

constexpr float RAD2DEG = 180.0f / std::numbers::pi_v<float>;
constexpr float DEG2RAD = std::numbers::pi_v<float> / 180.0f;

struct Vector2 {
    float x{}, y{};

    constexpr Vector2() noexcept = default;
    constexpr Vector2(float x, float y) noexcept : x(x), y(y) {}

    // Some Functions
    float Length() const noexcept {
        return static_cast<float>(std::sqrt(x * x + y * y));
    }

    float LengthSqr() const noexcept {
        return x * x + y * y;
    }

    Vector2 Normalize() const noexcept {
        float len = Length();
        return len != 0.f ? (*this / len) : Vector2{};
    }

    float Dot(const Vector2& other) const noexcept {
        return x * other.x + y * other.y;
    }

    float Distance(const Vector2& other) const noexcept {
        return (*this - other).Length();
    }

    bool IsZero(float tolerance = 0.001f) const noexcept {
        return std::fabs(x) < tolerance && std::fabs(y) < tolerance;
    }

    ImVec2 ToImVec2() const noexcept {
        return ImVec2(x, y);
    }

    // Operator Overloads
    Vector2 operator+(const Vector2& rhs) const noexcept {
        return { x + rhs.x, y + rhs.y };
    }

    Vector2 operator-(const Vector2& rhs) const noexcept {
        return { x - rhs.x, y - rhs.y };
    }

    Vector2 operator*(float scalar) const noexcept {
        return { x * scalar, y * scalar };
    }

    Vector2 operator/(float scalar) const noexcept {
        return { x / scalar, y / scalar };
    }

    Vector2& operator+=(const Vector2& rhs) noexcept {
        x += rhs.x; y += rhs.y;
        return *this;
    }

    Vector2& operator-=(const Vector2& rhs) noexcept {
        x -= rhs.x; y -= rhs.y;
        return *this;
    }

    Vector2& operator*=(float scalar) noexcept {
        x *= scalar; y *= scalar;
        return *this;
    }

    Vector2& operator/=(float scalar) noexcept {
        x /= scalar; y /= scalar;
        return *this;
    }
};

struct Vector3 {
    float x{}, y{}, z{};

    constexpr Vector3() noexcept = default;
    constexpr Vector3(float x, float y, float z) noexcept : x(x), y(y), z(z) {}

    // Some Functions
    float Length() const noexcept {
        return std::sqrt(x * x + y * y + z * z);
    }

    float LengthSqr() const noexcept {
        return x * x + y * y + z * z;
    }

    Vector3 Normalize() const noexcept {
        float len = Length();
        return len != 0.f ? (*this / len) : Vector3(0.f, 0.f, 0.f);
    }

    float Dot(const Vector3& other) const noexcept {
        return x * other.x + y * other.y + z * other.z;
    }

    Vector3 Cross(const Vector3& rhs) const noexcept {
        return {
            y * rhs.z - z * rhs.y,
            z * rhs.x - x * rhs.z,
            x * rhs.y - y * rhs.x
        };
    }

    Vector3 RelativeAngle()
    {
        return {
            std::atan2(-z, std::hypot(x, y)) * (180.0f / std::numbers::pi_v<float>),
            std::atan2(y, x) * (180.0f / std::numbers::pi_v<float>),
            0.0f
        };
    }

    float Distance(const Vector3& other) const noexcept {
        return (*this - other).Length();
    }

    Vector2 ToVector2() const noexcept {
        return Vector2{x, y};
    }

    ImVec2 ToImVec2() const noexcept {
        return ImVec2(x, y);
    }

    float AngleDifference(const Vector3& other) const noexcept {
        float deltaPitch = std::fabs(x - other.x);
        float deltaYaw = std::fabs(y - other.y);

        if (deltaPitch > 180.f) deltaPitch = 360.f - deltaPitch;
        if (deltaYaw > 180.f) deltaYaw = 360.f - deltaYaw;

        return std::sqrt(deltaPitch * deltaPitch + deltaYaw * deltaYaw);
    }

    bool IsZero(float tolerance = 0.001f) const noexcept {
        return std::fabs(x) < tolerance && std::fabs(y) < tolerance && std::fabs(z) < tolerance;
    }

    Vector3 WorldToScreen(Matrix4x4 vm)
    {
        float _x = vm[0][0] * x + vm[0][1] * y + vm[0][2] * z + vm[0][3];
        float _y = vm[1][0] * x + vm[1][1] * y + vm[1][2] * z + vm[1][3];
        float _w = vm[3][0] * x + vm[3][1] * y + vm[3][2] * z + vm[3][3];
        
        if (_w < 0.1f)
            return {0.0f, 0.0f, 0.0f};

        float _iw = 1.f / _w;
        _x *= _iw;
        _y *= _iw;

        float x = static_cast<float>(GetSystemMetrics(SM_CXSCREEN) / 2);
        float y = static_cast<float>(GetSystemMetrics(SM_CYSCREEN) / 2);

        x += 0.5f * _x * GetSystemMetrics(SM_CXSCREEN) + 0.5f;
        y -= 0.5f * _y * GetSystemMetrics(SM_CYSCREEN) + 0.5f;

        return { x, y, _w };
    }

    // Operator Overloads
    Vector3 operator+(const Vector3& rhs) const noexcept {
        return { x + rhs.x, y + rhs.y, z + rhs.z };
    }

    Vector3 operator-(const Vector3& rhs) const noexcept {
        return { x - rhs.x, y - rhs.y, z - rhs.z };
    }

    Vector3 operator*(float scalar) const noexcept {
        return { x * scalar, y * scalar, z * scalar };
    }

    Vector3 operator/(float scalar) const noexcept {
        return { x / scalar, y / scalar, z / scalar };
    }

    Vector3& operator+=(const Vector3& rhs) noexcept {
        x += rhs.x; y += rhs.y; z += rhs.z;
        return *this;
    }

    Vector3& operator-=(const Vector3& rhs) noexcept {
        x -= rhs.x; y -= rhs.y; z -= rhs.z;
        return *this;
    }

    Vector3& operator*=(float scalar) noexcept {
        x *= scalar; y *= scalar; z *= scalar;
        return *this;
    }

    Vector3& operator/=(float scalar) noexcept {
        x /= scalar; y /= scalar; z /= scalar;
        return *this;
    }
};

struct Vector4 {
    float x{}, y{}, z{}, w{};

    constexpr Vector4() noexcept = default;
    constexpr Vector4(float x, float y, float z, float w) noexcept : x(x), y(y), z(z), w(w) {}
};

struct C_UTL_VECTOR
{
    DWORD64 Count = 0;
    DWORD64 Data = 0;
};