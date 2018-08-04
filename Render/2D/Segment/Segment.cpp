#include "Segment.h"

Segment::Segment(const Vec3<float> &a, const Vec3<float> &b)
	:A(a), B(b)
{

}

double Segment::dist() const
{
	return A.distance(B);
}

void Segment::createLocus()
{
	Vec2<int> a(int(std::ceil(A.x)), int(std::ceil(A.y)));
	Vec2<int> b(int(std::ceil(B.x)), int(std::ceil(B.y)));

	if (a.x > b.x) std::swap(a, b);

	bool inverse = abs(a.y - b.y) < abs(a.x - b.x);

	for (int x = a.x; x <= b.x; ++x)
	{

	}
}