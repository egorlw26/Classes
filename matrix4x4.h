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

    Matrix4x4<T> multiply(const Matrix4x4<T> &other) const
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

    Vec4<T> multiply(Vec4<T> right) const
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
    }

    Matrix4x4<T> transpose()
    {
        for(int i =0; i<4; i++)
            for(int j=0; j<4; j++)
                if(j>i)
                {
                    T temp = elements[i*4 + j];
                    elements[i*4+j] = elements[j*4+i];
                    elements[j*4+i] = temp;
                }
        return *this;
    }

    Matrix4x4<T> swapRows(int i, int j)
    {
        for(int k=0; k<4; k++)
        {
            T temp = elements[i*4+k];
            elements[i*4+k] = elements[j*4+k];
            elements[j*4+k] = temp;
        }
        return *this;
    }

    Matrix4x4<T> swapColumns(int i, int j)
    {
        for(int k=0; k<4; k++)
        {
            T temp = elements[i + k*4];
            elements[i+k*4] = elements[j+k*4];
            elements[j+k*4] = temp;
        }
        return *this;
    }

    Matrix4x4<T> inverse()
    {
        Matrix4x4<T> res, temp = *this;
        res.identity();
        for(int i =0; i<4; i++)
        {
            if(temp.elements[i*4+i]==0)
            {
                for(int j=0; j<4; j++)
                    if(temp.elements[i+j*4]!=0)
                    {
                        temp.swapRows(i, j);
                        break;
                    }
            }

            for(int j = 0; j<4; j++)
            {
                if(j!=i)
                    temp.elements[i*4+j]= temp.elements[i*4+j]*1.0/temp.elements[i*4+i];
                res.elements[i*4+j] = res.elements[i*4+j]*1.0/temp.elements[i*4+i];
            }
           temp.elements[i*4+i] = 1;


            for(int j=0; j<4; j++)
            {
                if(j!=i)
                {
                    double el = temp.elements[j*4+i];
                    for(int k = 0; k<4; k++)
                    {
                        temp.elements[j*4+k]-=el*temp.elements[i*4+k];
                        res.elements[j*4+k]-=el*res.elements[i*4+k];
                    }
                }
            }

        }

        return res;
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

    friend Vec4<T> operator * (const Matrix4x4<T> &left, Vec4<T> right)
    {
        return left.multiply(right);
    }

    friend Matrix4x4<T> operator * (Vec4<T> left, const Matrix4x4<T> &right)
    {
        Matrix4x4<T> res;
        for(int i = 0; i<4; i++)
            for(int j = 0; j<4; j++)
                res.elements[i*4+j] += left[i]*right.elements[j];
        return res;
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
