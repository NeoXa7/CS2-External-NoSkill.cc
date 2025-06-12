#pragma once
#include <cmath>

struct Matrix4x4
{
    float* operator[](int index)
    {
        return matrix[index];
    }

    const float* operator[](int index) const
    {
        return matrix[index];
    }

    bool IsZero(float epsilon = 1e-6f) const
    {
        for (int row = 0; row < 4; ++row)
        {
            for (int col = 0; col < 4; ++col)
            {
                if (std::fabs(matrix[row][col]) > epsilon)
                    return false;
            }
        }
        return true;
    }

    float matrix[4][4];
};
