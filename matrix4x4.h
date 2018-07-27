#ifndef MATRIX4X4_H
#define MATRIX4X4_H
#include <iostream>
#include <cmath>
#include <vec4.h>
#define PI ((double)std::acos(-1))


template<typename T = long double>
class Matrix4x4
{
public:
    union
    {
        T elements[16];
        struct
        {
            T x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15;
        };
    };

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

    Matrix4x4<T>(T x0, T x1, T x2, T x3, T x4, T x5, T x6, T x7, T x8, T x9, T x10, T x11, T x12, T x13, T x14, T x15)
        : x0(x0), x1(x1), x2(x2), x3(x3), x4(x4), x5(x5), x6(x6), x7(x7), x8(x8), x9(x9), x10(x10), x11(x11), x12(x12), x13(x13), x14(x14), x15(x15)
    {}

    Matrix4x4<T> negative()
    {
        for(int i = 0; i<16; i++)
            elements[i]*=-1;
        return *this;
    }

    static Matrix4x4<T> identity()
    {
        Matrix4x4<T> res;
        for(int i =0; i<4; i++)
            for(int j = 0; j<4; j++)
                res.elements[i*4+j] = (i==j);
        return res;
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
        return  elements[0]*(elements[5]*(elements[10]*elements[15] - elements[11] * elements[14])
                + elements[6]*(elements[13]*elements[11] - elements[9]*elements[15])
                + elements[7]*(elements[9]*elements[14] - elements[13]*elements[10]))
                - elements[1]*(elements[4]*(elements[10]*elements[15] - elements[11] * elements[14])
                + elements[6]*(elements[12]*elements[11] - elements[8]*elements[15])
                + elements[7]*(elements[8]*elements[14] - elements[12]*elements[10]))
                + elements[2]*(elements[4]*(elements[9]*elements[15] - elements[11] * elements[13])
                + elements[5]*(elements[12]*elements[11] - elements[8]*elements[15])
                + elements[7]*(elements[8]*elements[13] - elements[12]*elements[9]))
                - elements[3]*(elements[4]*(elements[9]*elements[14] - elements[10] * elements[13])
                + elements[5]*(elements[12]*elements[10] - elements[8]*elements[14])
                + elements[6]*(elements[8]*elements[13] - elements[12]*elements[9]));
    }

    T determinant2()
    {
        int ans = 0;
        for(int i=0; i<4; i++)
        {
        }
    }

    Matrix4x4<T> transpose()
    {
        for(int i =0; i<3; i++)
            for(int j=i+1; j<4; j++)
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
        Matrix4x4<T> res;
        Matrix4x4<double> temp = *this;
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

    static Matrix4x4<T> translation(T x, T y, T z)
    {
        Matrix4x4<T> res;
        res.identity();
        res.elements[3] = x;
        res.elements[7] = y;
        res.elements[11] = z;
        return res;
    }

    static Matrix4x4<T> scaling(T x, T y, T z)
    {
        Matrix4x4<T> res;
        res.identity();
        res.elements[0] = x;
        res.elements[5] = y;
        res.elements[10] = z;
        return res;
    }

    static Matrix4x4<T> rotate(double angle, Vec4<T> vector)
    {
        double cos =std::cos((double)(angle*(PI/180.0))), sin = std::tan((double)(angle*(PI/180.0)));
        Matrix4x4<T> res (cos + vector.x*vector.x*(1 - cos), vector.x*vector.y*(1-cos) - vector.z*sin, vector.x*vector.z*(1-cos)  + vector.y*sin, 0,
                            vector.y*vector.x*(1-cos) + vector.z*sin, cos + vector.y*vector.y*(1-cos), vector.y*vector.z*(1-cos) - vector.x*sin, 0,
                            vector.z*vector.x*(1-cos) - vector.y*sin, vector.z*vector.y*(1-cos) + vector.x*sin, cos + vector.z*vector.z*(1-cos), 0,
                            0, 0, 0, 1);
        return res;
    }

    static Matrix4x4<T> rotateXY(double angle)
    {
        double cos = std::cos((double)(angle*(PI/180.0))), sin = std::tan((double)(angle*(PI/180.0)));
        Matrix4x4<T> res (cos, -sin, 0, 0,
                             sin, cos, 0, 0,
                             0, 0, 1, 0,
                             0, 0 ,0, 1);
        return res;
    }

    static Matrix4x4<T> rotateXZ(double angle)
    {
       double cos = std::cos((double)(angle*(PI/180.0))), sin = std::tan((double)(angle*(PI/180.0)));
       Matrix4x4<T> res (cos, 0, -sin, 0,
                             0, 1, 0, 0,
                             sin, 0, cos, 0,
                             0, 0 ,0, 1);
       return res;
    }

    static Matrix4x4<T> rotateZY(double angle)
    {
        double cos = std::cos((double)(angle*(PI/180.0))), sin = std::tan((double)(angle*(PI/180.0)));
        Matrix4x4<T> res (1, 0, 0, 0,
                             0, cos, -sin, 0,
                             0, sin, cos, 0,
                             0, 0, 0, 1);
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
