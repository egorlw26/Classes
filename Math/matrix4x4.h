#ifndef MATRIX4X4_H
#define MATRIX4X4_H
#include <iostream>
#include <math.h>
#include "vec3.h"
#include "vec4.h"

#define PI ((double)std::acos(-1))

template<typename T = long double>
class Matrix4x4
{
public:
	T elements[16];

	Matrix4x4()
	{
		for (int i = 0; i < 16; i++)
			elements[i] = 0;
	}

	Matrix4x4<T>(T mas[16])
	{
		for (int i = 0; i < 16; i++)
			elements[i] = mas[i];
	}

	Matrix4x4<T> negative()
	{
		for (int i = 0; i < 16; i++)
			elements[i] *= -1;
		return *this;
	}

	static Matrix4x4<T> identity()
	{
		Matrix4x4<T> res;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				res.elements[i * 4 + j] = (i == j);
		return res;
	}

	Matrix4x4<T> add(const Matrix4x4<T> &other) const
	{
		Matrix4x4<T> nMat;
		for (int i = 0; i < 16; i++)
			nMat.elements[i] = elements[i] + other.elements[i];
		return nMat;
	}

	Matrix4x4<T> substract(const Matrix4x4<T> &other) const
	{
		Matrix4x4<T> nMat;
		for (int i = 0; i < 16; i++)
			nMat.elements[i] = elements[i] - other.elements[i];
		return nMat;
	}

	template<typename U>
	Matrix4x4<T> multiply(U value)
	{
		for (int i = 0; i < 16; i++)
			elements[i] *= value;
		return *this;
	}

	Matrix4x4<T> multiply(const Matrix4x4<T> &other) const
	{
		Matrix4x4<T> nMat;

		for (int k = 0; k < 4; k++)
			for (int j = 0; j < 4; j++)
			{
				for (int i = 0; i < 4; i++)
					nMat.elements[j + k * 4] += elements[i + k * 4] * other.elements[i * 4 + j];
			}
		return nMat;
	}

	Vec4<T> multiply(Vec4<T> right) const
	{
		Vec4<T> vec(0, 0, 0, 0);
		for (int j = 0; j < 4; j++)
			for (int i = 0; i < 4; i++)
				vec[j] += right[i] * elements[j * 4 + i];
		return vec;
	}


	T determinant()
	{
		return  elements[0] * (elements[5] * (elements[10] * elements[15] - elements[11] * elements[14])
			+ elements[6] * (elements[13] * elements[11] - elements[9] * elements[15])
			+ elements[7] * (elements[9] * elements[14] - elements[13] * elements[10]))
			- elements[1] * (elements[4] * (elements[10] * elements[15] - elements[11] * elements[14])
				+ elements[6] * (elements[12] * elements[11] - elements[8] * elements[15])
				+ elements[7] * (elements[8] * elements[14] - elements[12] * elements[10]))
			+ elements[2] * (elements[4] * (elements[9] * elements[15] - elements[11] * elements[13])
				+ elements[5] * (elements[12] * elements[11] - elements[8] * elements[15])
				+ elements[7] * (elements[8] * elements[13] - elements[12] * elements[9]))
			- elements[3] * (elements[4] * (elements[9] * elements[14] - elements[10] * elements[13])
				+ elements[5] * (elements[12] * elements[10] - elements[8] * elements[14])
				+ elements[6] * (elements[8] * elements[13] - elements[12] * elements[9]));
	}

	T determinant2()
	{
		int ans = 0;
		for (int i = 0; i < 4; i++)
		{
		}
	}

	Matrix4x4<T> transpose()
	{
		for (int i = 0; i < 3; i++)
			for (int j = i + 1; j < 4; j++)
			{
				T temp = elements[i * 4 + j];
				elements[i * 4 + j] = elements[j * 4 + i];
				elements[j * 4 + i] = temp;
			}
		return *this;
	}

	Matrix4x4<T> swapRows(int i, int j)
	{
		for (int k = 0; k < 4; k++)
		{
			T temp = elements[i * 4 + k];
			elements[i * 4 + k] = elements[j * 4 + k];
			elements[j * 4 + k] = temp;
		}
		return *this;
	}

	Matrix4x4<T> swapColumns(int i, int j)
	{
		for (int k = 0; k < 4; k++)
		{
			T temp = elements[i + k * 4];
			elements[i + k * 4] = elements[j + k * 4];
			elements[j + k * 4] = temp;
		}
		return *this;
	}

	Matrix4x4<T> inverse()
	{
		Matrix4x4<T> res;
		Matrix4x4<double> temp = *this;
		res = identity();
		for (int i = 0; i < 4; i++)
		{
			if (temp.elements[i * 4 + i] == 0)
			{
				for (int j = 0; j < 4; j++)
					if (temp.elements[i + j * 4] != 0)
					{
						temp.swapRows(i, j);
						break;
					}
			}

			for (int j = 0; j < 4; j++)
			{
				if (j != i)
					temp.elements[i * 4 + j] = temp.elements[i * 4 + j] * 1.0 / temp.elements[i * 4 + i];
				res.elements[i * 4 + j] = res.elements[i * 4 + j] * 1.0 / temp.elements[i * 4 + i];
			}
			temp.elements[i * 4 + i] = 1;


			for (int j = 0; j < 4; j++)
			{
				if (j != i)
				{
					double el = temp.elements[j * 4 + i];
					for (int k = 0; k < 4; k++)
					{
						temp.elements[j * 4 + k] -= el * temp.elements[i * 4 + k];
						res.elements[j * 4 + k] -= el * res.elements[i * 4 + k];
					}
				}
			}

		}

		return res;
	}

	static Matrix4x4<T> translation(Vec4<T> vector)
	{
		Matrix4x4<T> res;
		res = identity();
		res.elements[3] = vector.x;
		res.elements[7] = vector.y;
		res.elements[11] = vector.z;
		return res;
	}

	static Matrix4x4<T> scaling(Vec4<T> vector)
	{
		Matrix4x4<T> res;
		res = identity();
		res.elements[0] = vector.x;
		res.elements[5] = vector.y;
		res.elements[10] = vector.z;
		return res;
	}

	static Matrix4x4<T> rotate(double angle, Vec4<T> vector)
	{
		double cos = std::cos((double)(angle*(PI / 180.0))), sin = std::tan((double)(angle*(PI / 180.0)));
		T mas[] = { cos + vector.x*vector.x*(1 - cos), vector.x*vector.y*(1 - cos) - vector.z*sin, vector.x*vector.z*(1 - cos) + vector.y*sin, 0,
							vector.y*vector.x*(1 - cos) + vector.z*sin, cos + vector.y*vector.y*(1 - cos), vector.y*vector.z*(1 - cos) - vector.x*sin, 0,
							vector.z*vector.x*(1 - cos) - vector.y*sin, vector.z*vector.y*(1 - cos) + vector.x*sin, cos + vector.z*vector.z*(1 - cos), 0,
							0, 0, 0, 1 };
		Matrix4x4<T> res(mas);
		return res;
	}

	static Matrix4x4<T> perspective(double angle, double aspect, double n, double f)
	{
		T mas[] = { std::ctg(angle / 2 * PI / 180) / aspect, 0, 0, 0,
				   0, std::ctg(angle / 2 * PI / 180), 0, 0,
				  0, 0, (f + n) / (f - n), 1,
				  0, 0, -2 * f*n / (f - n), 0 };
		Matrix4x4<T> res(mas);
		return res;
	}

	static Matrix4x4<T> perspective(double left, double right, double top, double bottom, double n, double f)
	{
		double a = f - n, b = right - left, c = top - bottom;
		T mas[] = { 2 * n / b, 0, (right + left) / b, 0,
				  0, 2 * n / c, (top + bottom) / c, 0,
				  0, 0, -(f + n) / a, -2 * f*n / a,
				  0, 0, -1, 0 };
		Matrix4x4<T> res(mas);
		return res;
	}

	static Matrix4x4<T> orthographic(double left, double right, double top, double bottom, double n, double f)
	{
		double a = f - n, b = right - left, c = top - bottom;
		T mas[] = { 2 / b, 0, 0, -(right + left) / b,
				  0, 2 / c, 0, -(top + bottom) / c,
				  0, 0, -2 / a, -(f + n) / a,
				  0, 0, 0, 1 };
		Matrix4x4<T> res(mas);
		return res;
	}

	Matrix4x4<T> operator = (const Matrix4x4<T> &right)
	{
		for (int i = 0; i < 16; i++)
			elements[i] = right.elements[i];
		return *this;
	}

	friend Matrix4x4<T> operator + (const Matrix4x4<T> &left, const Matrix4x4<T> &right)
	{
		return left.add(right);
	}

	friend Matrix4x4<T> operator - (const Matrix4x4<T> &left, const Matrix4x4<T> &right)
	{
		return left.substract(right);
	}

	template<typename U>
	friend Matrix4x4<T> operator * (const Matrix4x4<T> &left, U value)
	{
		return left.multiply(value);
	}

	template<typename U>
	friend Matrix4x4<T> operator * (U value, const Matrix4x4<T> &right)
	{
		return right.multiply(value);
	}

	friend Matrix4x4<T> operator * (const Matrix4x4<T> &left, const Matrix4x4<T> &right)
	{
		return left.multiply(right);
	}

	friend Vec4<T> operator * (const Matrix4x4<T> &left, Vec4<T> right)
	{
		return left.multiply(right);
	}

	friend Matrix4x4<T> operator * (Vec4<T> left, const Matrix4x4<T> &right)
	{
		Matrix4x4<T> res;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				res.elements[i * 4 + j] += left[i] * right.elements[j];
		return res;
	}

	friend std::ostream& operator << (std::ostream& os, const Matrix4x4<T> &matrix)
	{
		for (int i = 0; i < 16; i++)
		{
			os << matrix.elements[i];
			(i + 1) % 4 == 0 ? std::cout << std::endl : std::cout << ' ';
		}
		return os;
	}

};

#endif // MATRIX4X4_H
