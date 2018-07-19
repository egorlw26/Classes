#ifndef MATRIX4X4_H
#define MATRIX4X4_H
#include <iostream>
#include <cmath>

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
        T mas[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
        for(int i = 0; i<16; i++)
            elements[i] = mas[i];
        return *this;
    }

    Matrix4x4<T> add(Matrix4x4<T> &other) const
    {
        T nMat[16];
        for(int i = 0; i<16; i++)
            nMat[i] = elements[i] + other.elements[i];
        return Matrix4x4<T>(nMat);
    }

    Matrix4x4<T> substract(Matrix4x4<T> &other) const
    {
        T nMat[16];
        for(int i = 0; i<16; i++)
            nMat[i] = elements[i] - other.elements[i];
        return Matrix4x4<T>(nMat);
    }

    template<typename U>
    Matrix4x4<T> multiply(U value)
    {
        for(int i = 0; i<16; i++)
            elements[i] *= value;
        return *this;
    }

    Matrix4x4<T> multiply(Matrix4x4<T> &other)
    {
        T nMat[16];

        for(int k = 0; k<4; k++)
            for(int j = 0; j<4; j++)
            {
                int el = 0;
                for(int i=0; i<4; i++)
                    el += elements[i+k*4] * other.elements[i*4+j];
                nMat[j+k*4] = el;
            }
        return Matrix4x4<T>(nMat);
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

    friend std::ostream& operator << (std::ostream& os, const Matrix4x4<T> &matrix)
    {
        for(int i =0; i<16; i++)
        {
            os<<matrix.elements[i]<<' ';
            if((i+1)%4==0) os<<std::endl;
        }
        return os;
    }
};

#endif // MATRIX4X4_H
