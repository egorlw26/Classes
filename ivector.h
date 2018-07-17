#ifndef IVECTOR_H
#define IVECTOR_H

class IVector
{
public:
    IVector();
    virtual IVector multiply(double x) = 0;
    virtual IVector negative() = 0;
    virtual IVector add(const IVector &other) = 0;
    virtual IVector substract(const IVector &other) = 0;
    virtual double dot(const IVector &other) = 0;
    virtual IVector cross(const IVector &other) = 0;
    virtual IVector normalize() = 0;
    virtual double magnitude() = 0;

    virtual ~IVector() = default;

};

#endif // IVECTOR_H
