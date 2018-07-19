#ifndef MATRIX4X4_H
#define MATRIX4X4_H
#include <iostream>
#include <cmath>
#include <vec4.h>

template<typename T = long double>
class Matrix4x4
{
public:
    T elements[16];
    Matrix4x4()
    {
        for(int i = 0; i<16; i++)
            elements[i] = 0;
    }

    Matrix4x4<T>(T mas[16])
    {
        for(int i = 0; i<16; i++)
            elements[i] = mas[i];
    }

    Matrix4x4<T> negative()
    {
        for(int i = 0; i<16; i++)
            elements[i]*=-1;
        return *this;
    }

    Matrix4x4<T> identity()
    {
        for(int i =0; i<4; i++)
            for(int j = 0; j<4; j++)
                elements[i*4+j] = (i==j);
        return *this;
    }

    Matrix4x4<T> add(const Matrix4x4<T> &other) const
    {
        Matrix4x4<T> nMat;
        for(int i = 0; i<16; i++)
            nMat.elements[i] = elements[i] + other.elements[i];
        return nMat;
    }

    Matrix4x4<T> substract(const Matrix4x4<T> &other) const
    {
        Matrix4x4<T> nMat;
        for(int i = 0; i<16; i++)
            nMat.elements[i] = elements[i] - other.elements[i];
        return nMat;
    }

    template<typename U>
    Matrix4x4<T> multiply(U value)
    {
        for(int i = 0; i<16; i++)
            elements[i] *= value;
        return *this;
    }

    Matrix4x4<T> multiply(const Matrix4x4<T> &other)
    {
        Matrix4x4<T> nMat;

        for(int k = 0; k<4; k++)
            for(int j = 0; j<4; j++)
            {
                for(int i=0; i<4; i++)
                    nMat.elements[j+k*4] += elements[i+k*4] * other.elements[i*4+j];
            }
        return nMat;
    }

    Vec4<T> multiply(Vec4<T> right)
    {
        Vec4<T> vec(0, 0, 0, 0);
        for(int j = 0; j<4; j++)
            for(int i=0; i<4; i++)
                vec[j] += right[i]*elements[j*4+i];
        return vec;
    }


    T determinant()
    {
        T a1 = elements[0]*(elements[5]*(elements[10]*elements[15] - elements[11] * elements[14])
                + elements[6]*(elements[13]*elements[11] - elements[9]*elements[15])
                + elements[7]*(elements[9]*elements[14] - elements[13]*elements[10]));

        T a2 = elements[1]*(elements[4]*(elements[10]*elements[15] - elements[11] * elements[14])
                + elements[6]*(elements[12]*elements[11] - elements[8]*elements[15])
                + elements[7]*(elements[8]*elements[14] - elements[12]*elements[10]));

        T a3 = elements[2]*(elements[4]*(elements[9]*elements[15] - elements[11] * elements[13])
                + elements[5]*(elements[12]*elements[11] - elements[8]*elements[15])
                + elements[7]*(elements[8]*elements[13] - elements[12]*elements[9]));

        T a4 = elements[3]*(elements[4]*(elements[9]*elements[14] - elements[10] * elements[13])
                + elements[5]*(elements[12]*elements[10] - elements[8]*elements[14])
                + elements[6]*(elements[8]*elements[13] - elements[12]*elements[9]));

        return a1 - a2 + a3 - a4;

        //remade more optimazed!!!
    }

    Matrix4x4<T> transpose()
    {
        int f[] = {1, 2, 3, 6, 7, 11}, t[] = {4, 8, 12, 9, 13, 14};
        for(int i = 0; i<6; i++)
        {
            T temp = elements[f[i]];
            elements[f[i]] = elements[t[i]];
            elements[t[i]] = temp;
        }
        return *this;
    }

    Matrix4x4<T> operator = (const Matrix4x4<T> &right)
    {
        for(int i = 0; i<16; i++)
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

    friend std::ostream& operator << (std::ostream& os, const Matrix4x4<T> &matrix)
    {
        for(int i =0; i<16; i++)
        {
            os<<matrix.elements[i];
            (i+1)%4==0 ? std::cout<<std::endl : std::cout<<' ';
        }
        return os;
    }
};

#endif // MATRIX4X4_H
