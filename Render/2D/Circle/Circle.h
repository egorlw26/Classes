#pragma once
#include <vector>

#include "../../../Math/Math.h"

class Circle
{
public:
	Circle(const Vec3<float> &center, const Vec3<float> &dot);
	Circle(const Vec3<float> &center, float radius);

	void calculateLocus();
	inline std::vector<Vec3<float>> getLocus() const { return m_locus; };

private:
	Vec3<float> m_center;
	float m_radius;

	std::vector<Vec3<float>> m_locus;
};
