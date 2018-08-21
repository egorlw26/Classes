#pragma once
#include <vector>

#include "../../../Math/Math.h"
#include "../../../Renderable.h"

class Segment : public Renderable
{
public:
	Segment(const Vec3<float> &a, const Vec3<float> &b,const Color &color);

	double dist() const;

	bool intersectWithRay(const Ray &ray, Vec3<float> &intersection) override;

	inline Color getColor() const override { return m_color; };
	inline Vec3<float> getA() const { return A; };
	inline Vec3<float> getB() const { return B; };

private:
	void createLocus() override;
	void createVolumeBox() override;

	Vec3<float> A;
	Vec3<float> B;
	Vec3<float> AB;
	Color m_color;
};
