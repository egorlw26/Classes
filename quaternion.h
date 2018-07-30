#ifndef QUATERNION_H
#define QUATERNION_H
#include <vec3.h>
#include <vec4.h>
#include <matrix4x4.h>

template<typename T = long double>
class Quaternion
{
public:
    union
    {
        Vec4<T> elements;
        struct
        {
            T x, y, z, w;
        };
    };

    Quaternion():
        x(0), y(0), z(0), w(0)
    {}

    Quaternion<T>(T x, T y, T z, T w):
        x(x), y(y), z(z), w(w)
    {}

    Quaternion<T>(Vec3<T> vec, T a):
        x(vec.x), y(vec.y), z(vec.z), w(a)
    {}

    Quaternion<T> add (const Quaternion<T> &other) const
    {
        Quaternion<T> res(x + other.x, y+other.y, z+other.z, w+other.w);
        return res;
    }

    Quaternion<T> conjugate() const
    {
        Quaternion<T> res (-x, -y, -z, w);
        return res;
    }


};

#endif // QUATERNION_H
