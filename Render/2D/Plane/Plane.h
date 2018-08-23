#pragma once


#include "../../../Math/Math.h"
#include "../../../Renderable.h"


class Plane : public Renderable
{
public:
	Plane(const Vec3<float> &a, const Vec3<float> &b, const Vec3<float> &c, const Color &color); //three points, not point & vectors!

	bool intersectWithRay(const Ray &ray, Vec3<float> &intersection) override;

	inline Color getColor() const override { return m_color; };

	bool createEquation(Vec4<float> &equation);

private:
	void createLocus() override;
	void createVolumeBox() override;

	Vec3<float> A;
	Vec3<float> B;
	Vec3<float> C;
	Vec3<float> AB;
	Vec3<float> AC;
	Color m_color;
};

