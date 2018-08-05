#pragma once

#include "../../../Renderable.h"
#include "../../../Math/Math.h"

class Sphere : public Renderable
{
public:
	Sphere(const Vec3<float> &center, float radius);

	bool intersectWithRay(const Ray &ray,Vec3<float> &intersection) override;
private:
	void createLocus() override;
	void createVolumeBox() override;

	Vec3<float> m_center;
	float m_radius;
};