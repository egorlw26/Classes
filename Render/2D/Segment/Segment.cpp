#include "Segment.h"

Segment::Segment(const Vec3<float> &a, const Vec3<float> &b)
	:A(a), B(b)
{

}

double Segment::dist() const
{
	return A.distance(B);
}

void Segment::createLocus()
{

}

void Segment::createVolumeBox()
{

}

bool Segment::intersectWithRay(const Ray &ray, Vec3<float> &intersection)
{
	return true;
}