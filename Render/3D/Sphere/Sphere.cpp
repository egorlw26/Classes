#include "Sphere.h"

Sphere::Sphere(const Vec3<float> &center, float radius, const Color &color)
	:m_center(center), m_radius(radius), m_color(color)
{

}

bool Sphere::intersectWithRay(const Ray &ray, Vec3<float> &intersection)
{
	Vec3<float> origin = ray.getOrigin();
	Vec3<float> direction = ray.getDirection();
	Vec3<float> toCenter = m_center - origin;

	float a = Vec3<float>::dot(direction, direction);
	float b = 2 * Vec3<float>::dot(direction, toCenter);
	float c = Vec3<float>::dot(toCenter, toCenter) - m_radius * m_radius;

	float disc = b * b - 4 * a*c;
	if (disc < 0) return false;
	disc = sqrt(disc);
	float minDist = std::fmin((-b + disc) / (2 * a), (-b - disc) / (2 * a));
	intersection = origin + minDist * direction;
	return true;
}

void Sphere::createLocus()
{

}

void Sphere::createVolumeBox()
{

}