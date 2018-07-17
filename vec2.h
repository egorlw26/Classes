#ifndef VEC2_H
#define VEC2_H
#include<cmath>
#include<iostream>

template<typename T = long double>
class Vec2
{
public:
    T x, y;
    Vec2()
        : x(0), y(0)
    {}

    Vec2<T>(T x, T y)
        : x(x), y(y)
    {}

    template<typename U>
    Vec2<T> multiply(U _x)
    {
        x*=_x;
        y*=_x;
        return *this;
    }

    Vec2<T> negative()
    {
        this->multiply(-1);
        return *this;
    }

    Vec2<T> add(const Vec2<T> &other) const
    {
        return Vec2(x + other.x, y + other.y);
    }

    Vec2<T> substract(const Vec2<T> &other) const
    {
        return Vec2(x - other.x, y - other.y);
    }

    double dot(const Vec2<T> &other)
    {
        return (x*other.x + y*other.y);
    }

    double magnitude()
    {
        return sqrt(x*x + y*y);
    }

    Vec2<T> normalize()
    {
        if(this->magnitude() != 0)
            this->multiply(1.0/this->magnitude());
        return *this;
    }


    Vec2<T> operator =(const Vec2<T> &right)
    {
        x = right.x;
        y = right.y;
        return *this;
    }

    bool operator >(const Vec2<T> &right)
    {
        if(x==right.x)
            return (y>right.y);
        return (x>right.x);
    }

    bool operator >=(const Vec2<T> &right)
    {
        return (*this > right || *this == right);
    }

    bool operator <(const Vec2<T> &right)
    {
        if(x==right.x)
            return (y<right.y);
        return (x<right.x);
    }

    bool operator <=(const Vec2<T> &right)
    {
        return (*this<right || *this == right);
    }

    bool operator == (const Vec2<T> &right)
    {
        return (x==right.x && y==right.y);
    }

    friend Vec2<T> operator -(Vec2<T> &vec)
    {

        vec.negative();
        return vec;

    }

    friend Vec2<T> operator + (Vec2<T> &left, const Vec2<T> &right)
    {
        return left.add(right);
    }

    friend Vec2<T> operator - (Vec2<T> &left, const Vec2<T> &right)
    {
        return left.substract(right);
    }

    template<typename U>
    friend Vec2<T> operator * (Vec2<T> &left, U value)
    {
        Vec2<T> temp = left;
        return temp.multiply(value);
    }

    template<typename U>
    friend Vec2<T> operator * (U value, Vec2<T> &right)
    {
        Vec2<T> temp = right;
        return temp.multiply(value);
    }

    friend std::ostream& operator<<(std::ostream& os, const Vec2<T> &vector)
    {
        os<<"("<<vector.x<<";"<<vector.y<<")";
        return os;
    }

};

#endif // VEC2_H
