#pragma once
#include <vector>

#include "Point.h"

class Segment
{
public:
	Segment(const Point &a, const Point &b);

	double dist() const;

	void calculateLocus();
	inline std::vector<Point> getLocus() const { return m_locus; };

private:
	Point A;
	Point B;

	std::vector<Point> m_locus;

};
