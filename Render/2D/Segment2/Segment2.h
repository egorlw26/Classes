#pragma once
#include <vector>

#include "../../../Math/Math.h"
#include "../../../Renderable.h"

class Segment2 : public Renderable
{
public:
	Segment2(const Vec3<float> &a, const Vec3<float> &b, const Color &color);

	double dist() const;

	bool intersectWithRay(const Ray &ray, Vec3<float> &intersection) override;

	inline Color getColor() const override { return m_color; };

private:
	void createLocus() override;
	void createVolumeBox() override;
	void gauss(float *&mas);

	Vec3<float> A;
	Vec3<float> B;
	const Color m_color;
	Vec3<float> AB;
};
