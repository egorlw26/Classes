#include "Circle.h"

Circle::Circle(const Vec3<float> &center, float radius)
	:m_center(center),m_radius(radius)
{

}

Circle::Circle(const Vec3<float> &center, const Vec3<float> &dot)
	:m_center(center),m_radius(center.distance(dot))
{

}

