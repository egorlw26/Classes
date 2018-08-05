#pragma once
#include <vector>

#include "../../../Math/Math.h"
#include "../../../Renderable.h"

class Segment : public Renderable
{
public:
	Segment(const Vec3<float> &a, const Vec3<float> &b);

	double dist() const;

	bool intersectWithRay(const Ray &ray, Vec3<float> &intersection) override;

private:
	void createLocus() override;
	void createVolumeBox() override;

	Vec3<float> A;
	Vec3<float> B;

};
