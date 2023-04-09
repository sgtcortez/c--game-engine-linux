#pragma once

namespace Math
{

    const static float PI = 3.1415926535f;

    float to_degress(const float radians)
    {
        return radians * 180.0f / PI;
    }    

    template <typename T>
    T negate(T original)
    {
        return -1 * original;
    }

}