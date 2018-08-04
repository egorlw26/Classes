#ifndef VEC4_H
#define VEC4_H
#include <iostream>
#include "vec3.h"

template<typename T = long double>
class Vec4
{
public:
    union
    {
        T a[4];
        struct
        {
            T x, y, z, w;
        };

    };

    Vec4()
        : x(0), y(0), z(0), w(0)
    {}

    Vec4<T>(T x, T y, T z, T w)
        : x(x), y(y), z(z), w(w)
    {}

    T& operator[] (int n)
    {
        return a[n];
    }

    template<typename U>
    Vec4<T> multiply(U _x)
    {
        x*=_x;
        y*=_x;
        z*=_x;
        return *this;
    }

    /*Vec3<T> toVec3 ()
    {
        Vec3<T> res;
        res.x = x/w;
        res.y = y/w;
        res.z = z/w;
        return res;
    }*/

    friend std::ostream& operator << (std::ostream& os, const Vec4<T> &vec)
    {
        os<<'('<<vec.x<<','<<vec.y<<','<<vec.z<<','<<vec.w<<')';
        return os;
    }
};

#endif // VEC4_H
