#pragma once
#include "Math/Math.h"

class Ray
{
public:
	Ray(const Vec3<float> &start, const Vec3<float> &direction);

	inline Vec3<float> getOrigin() const { return m_origin; };
	inline Vec3<float> getDirection() const { return m_direction; };

private:
	Vec3<float> m_origin;
	Vec3<float> m_direction;
};
