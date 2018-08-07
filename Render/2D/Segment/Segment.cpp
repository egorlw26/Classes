#include "Segment.h"

Segment::Segment(const Vec3<float> &a, const Vec3<float> &b, const Color &color)
	:A(a), B(b), m_color(color)
{
	AB = B - A;
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
	Vec3<float> o = ray.getOrigin();
	Vec3<float> d = ray.getDirection();
	Vec3<float> oa = A - o;

	//in different planes
	float det = oa.x*(AB.y*d.z - AB.z*d.y) - AB.x*(oa.y*d.z - d.y*oa.z) + d.x*(oa.y*AB.z - oa.z*AB.y);
	float det2 = Vec3<float>::dot(oa, Vec3<float>::cross(AB, d));

	if (std::abs(det2 - 0) > 1e-1)
		return false;

	Vec3<float> n = Vec3<float>::cross(d, AB);
	Vec3<float> pd = Vec3<float>::cross(n, d);

	float aopd = Vec3<float>::dot(o - A, pd);
	float abpd = Vec3<float>::dot(AB, pd);

	float u = aopd / abpd;

	Vec3<float> pab = Vec3<float>::cross(n, AB);

	float oapab = Vec3<float>::dot(oa, pab);
	float dpab = Vec3<float>::dot(d, pab);

	float t = oapab / dpab;

	Vec3<float> sub2 = (A + (AB * u)) - (o + (d * t));
	sub2.x = std::abs(sub2.x);
	sub2.y = std::abs(sub2.y);
	sub2.z = std::abs(sub2.z);
	Vec3<float> eps(1e-4, 1e-4, 1e-4);
	if (u > 0 && u < 1 && sub2 < eps) return true;
	else return false;
}