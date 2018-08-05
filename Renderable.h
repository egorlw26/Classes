#pragma once
#include "Ray.h"
#include "Math/Math.h"
#include "Render/Color/Color.h"

class Renderable
{
public:
	virtual void createVolumeBox() = 0;
	virtual void createLocus() = 0;
	virtual bool intersectWithRay(const Ray &ray,Vec3<float> &intersection) = 0;
	virtual Color getColor() const = 0;
};
