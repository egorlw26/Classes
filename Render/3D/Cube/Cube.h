#pragma once

#include "../../../Math/Math.h"
#include "../../../Renderable.h"
#include "../../../Ray.h"

class Cube : public Renderable
{
public:
	Cube(const Vec3<float> &center, float edge);
	bool intersectWithRay(const Ray &ray) override;

private:
	//void createVolumeBox() override;
	//void createLocus() override;

	Vec3<float> m_center;
	float m_edgeLength;

	//future
	//Vec<float> v1,v2;
};
