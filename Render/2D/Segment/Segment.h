#pragma once
#include <vector>

#include "../../../Math/Math.h"
#include "../../../Renderable.h"

class Segment : public Renderable
{
public:
	Segment(const Vec3<float> &a, const Vec3<float> &b);

	double dist() const;

	inline std::vector<Vec3<float>> getLocus() const { return m_locus; };

private:
	void createLocus() override;
	//void createVolumeBox() override;

	Vec3<float> A;
	Vec3<float> B;

	std::vector<Vec3<float>> m_locus;

};
