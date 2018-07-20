#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <vec2.h>
#include <vec3.h>
#include <vec4.h>
#include <matrix4x4.h>

int main()
{
    double m[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    Matrix4x4<double> mat(m), ma;
    std::cout<<mat<<std::endl;
    std::cout<<mat.transpose();
    return 0;
}
