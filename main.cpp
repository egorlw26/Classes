#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <vec2.h>
#include <vec3.h>

int main()
{
    Vec3<> ector(2, 3, 5), vec(4, 5, 1);
    std::cout<<2*ector+vec<<ector<<vec<<std::endl;

    return 0;
}
