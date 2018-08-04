#pragma once
#include "Math/Math.h"
#include "Render/Color/Color.h"

class Light
{
public:
	Light(const Vec3<float> &position, const Color &color = Color::White);

private:
	Vec3<float> m_position;
	Color m_color;

	//maybe later
	//float intensity;
};
