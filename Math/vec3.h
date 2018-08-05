#ifndef VEC3_H
#define VEC3_H
#include <iostream>
#include "vec4.h"

template<typename T = long double>
class Vec3
{
public:
	T x, y, z;
	Vec3()
		: x(0), y(0), z(0)
	{}

	Vec3<T>(T x, T y, T z)
		: x(x), y(y), z(z)
	{}

	template<typename U>
	Vec3<T> multiply(U _x)
	{
		x *= _x;
		y *= _x;
		z *= _x;
		return *this;
	}

	Vec3<T> negative()
	{
		this->multiply(-1);
		return *this;
	}

	Vec3<T>& add(const Vec3<T> &other) const
	{
		Vec3<T> res(x + other.x, y + other.y, z + other.z);
		return res;
	}

	Vec3<T>& substract(const Vec3<T> &other) const
	{
		Vec3<T> res(x - other.x, y - other.y, z - other.z);
		return res;
	}

	double dot(const Vec3<T> &other)
	{
		return (x*other.x + y * other.y + z * other.z);
	}

	Vec3<T> cross(const Vec3<T> &other)
	{
		return Vec3<T>(y*other.z - z * other.y, z*other.x - x * other.z, x*other.y - y * other.x);
	}

	double magnitude()
	{
		return sqrt(x*x + y * y + z * z);
	}

	template<typename U>
	double distance(const Vec3<U> &other) const
	{
		return (*this - other).magnitude();
	}

	Vec3<T> normalize()
	{
		this->multiply(1.0 / this->magnitude());
		return *this;
	}

	Vec4<T> toVec4(T w)
	{
		Vec4<T> res;
		res.x = x * w;
		res.y = y * w;
		res.z = z * w;
		res.w = w;
		return res;
	}

	Vec3<T> operator = (const Vec3<T> &right)
	{
		x = right.x;
		y = right.y;
		z = right.z;
		return *this;
	}

	bool operator > (const Vec3<T> &right)
	{
		if (x == right.x && y == right.y)
			return (z > right.z);
		if (x == right.x)
			return (y > right.y);
		return (x > right.x);
	}

	bool operator >= (const Vec3<T> &right)
	{
		return (*this > right || *this == right);
	}

	bool operator < (const Vec3<T> &right)
	{
		return !(*this > right);
	}

	bool operator <= (const Vec3<T> &right)
	{
		return (*this < right || *this == right);
	}

	bool operator == (const Vec3<T> &right)
	{
		return (x == right.x && y == right.y && z == right.z);
	}

	friend Vec3<T> operator -(Vec3<T> &vec)
	{
		vec.negative();
		return vec;
	}

	friend Vec3<T>& operator + (const Vec3<T> &left, const Vec3<T> &right)
	{
		return left.add(right);
	}

	friend Vec3<T>& operator - (const Vec3<T> &left, const Vec3<T> &right)
	{
		return left.substract(right);
	}

	template<typename U>
	friend Vec3<T> operator * (const Vec3<T> &left, U value)
	{
		Vec3<T> temp = left;
		return temp.multiply(value);
	}

	template<typename U>
	friend Vec3<T> operator * (U value, const Vec3<T> &right)
	{
		Vec3<T> temp = right;
		return temp.multiply(value);
	}

	friend std::ostream& operator<<(std::ostream& os, const Vec3<T> &vector)
	{
		os << '(' << vector.x << ';' << vector.y << ';' << vector.z << ')';
		return os;
	}
};

#endif // VEC3_H
