#ifndef VEC4_H
#define VEC4_H
#include <iostream>

template<typename T = long double>
class Vec4
{
public:
    T x, y, z, w;
    Vec4()
        : x(0), y(0), z(0), w(0)
    {}

    Vec4<T>(T x, T y, T z, T w)
        : x(x), y(y), z(z), w(w)
    {}

    T& operator[] (int n)
    {
        switch (n) {
        case 0:
            return x;
            break;
        case 1:
            return y;
            break;
        case 2:
            return z;
            break;
        case 3:
            return w;
            break;
        default:
            break;
        }
    }

    friend std::ostream& operator << (std::ostream& os, const Vec4<T> &vec)
    {
        os<<'('<<vec.x<<','<<vec.y<<','<<vec.z<<','<<vec.w<<')';
        return os;
    }
};

#endif // VEC4_H
