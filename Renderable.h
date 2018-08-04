#pragma once
#include "Ray.h"
#include "Math/Math.h"

class Renderable
{
public:
	virtual void createVolumeBox() = 0;
	virtual void createLocus() = 0;
	virtual bool intersectWithRay(const Ray &ray) = 0;
};
