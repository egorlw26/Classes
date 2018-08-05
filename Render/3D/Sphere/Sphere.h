#pragma once

#include "../../../Renderable.h"
#include "../../../Math/Math.h"
#include "../../Color/Color.h"

class Sphere : public Renderable
{
public:
	Sphere(const Vec3<float> &center, float radius,const Color &color);

	bool intersectWithRay(const Ray &ray,Vec3<float> &intersection) override;

	inline Color getColor() const override { return m_color; };

private:
	void createLocus() override;
	void createVolumeBox() override;

	Vec3<float> m_center;
	float m_radius;
	Color m_color;
};