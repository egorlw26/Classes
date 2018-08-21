#include "Segment2.h"

#define EPS 2000

Segment2::Segment2(const Vec3<float> &a, const Vec3<float> &b, const Color &color)
	:A(a), B(b), m_color(color)
{
	AB = B - A;
}

double Segment2::dist() const
{
	return A.distance(B);
}

void Segment2::createLocus()
{

}

void Segment2::createVolumeBox()
{

}

void gauss(float *&mas)
{
	
}


bool Segment2::intersectWithRay(const Ray &ray, Vec3<float> &intersection)
{
	Vec3<float> o = ray.getOrigin();
	Vec3<float> d = ray.getDirection();

	//our line: o + Ld
	//segment: A + MB
	
	
	
	if (o > d)
	{
		Vec3<float> temp = o;
		o = d;
		d = temp;
	}

	float mas[] = { -(B.x - A.x),  d.x, - o.x + A.x,
					 -(B.y - A.y), d.y, - o.y + A.y,
					 -(B.z - A.z), d.z, - o.z + A.z };

	if (std::fabs(mas[0] * (mas[4] * mas[8] - mas[5] * mas[7]) - mas[1] * (mas[3] * mas[8] - mas[5] * mas[6]) + mas[2] * (mas[3] * mas[7] - mas[4] * mas[6])) > EPS)
		return false;

	int rangInside = 0;
	int rangOutside = 0;

	for(int i=0; i<3; i++)
		if (std::fabs(mas[i * 3]) > EPS || std::fabs(mas[i * 3 + 1]) > EPS)
		{
			rangInside = 1;
			rangOutside = 1;
			break;
		}

	for(int i = 0; i<2; i++)
		for(int j=i+1; j<3; j++)
			if (std::fabs(mas[i * 3] * mas[j * 3 + 1] - mas[j * 3] * mas[i * 3 + 1]) > EPS)
			{
				rangInside = 2;
				rangOutside = 2;
				break;
			}

	if(rangInside == 1)
		for (int i = 0; i<2; i++)
			for (int j = i + 1; j<3; j++)
				for(int k=0; k<2; k++)
				if (std::fabs(mas[i * 3 + k] * mas[j * 3 + 2] - mas[j * 3 + k] * mas[i * 3 + 2]) > EPS)
				{
					rangOutside = 2;
					break;
				}


	if (rangInside != rangOutside)
		return false;

	for (int i = 0; i < 2; i++)
	{
		if (mas[i * 3 + i] == 0)
		{
			for (int j = 0; j < 3; j++)
				if (mas[j * 3 + i] != 0)
				{
					for (int k = 0; k < 3; k++)
					{
						float temp = mas[j * 3 + k];
						mas[j * 3 + k] = mas[i * 3 + k];
						mas[i * 3 + k] = temp;
					}

					break;
				}

		}
		float el = mas[i * 3 + i];
		for (int j = 2; j >= 0; j--)
			mas[i * 3 + j] /= el;

		for (int j = 0; j < 3; j++)
			if (j != i)
			{
				float el = mas[j * 3 + i];
				for (int k = 0; k < 3; k++)
					mas[j * 3 + k] -= el * mas[i * 3 + k];
			}
	}

	for (int i = 0; i < 3; i++)
		if (mas[i * 3] != 0)
			return (mas[i * 3 + 2] >= 0 && mas[i * 3 + 2] <= 1);

}

