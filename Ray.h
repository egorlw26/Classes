#pragma once
#include "Math/Math.h"

class Ray
{
public:
	Ray(const Vec3<float> &start, const Vec3<float> &direction);

	inline Vec3<float> getStart() const { return m_start; };

private:
	Vec3<float> m_start;
	Vec3<float> m_direction;
};