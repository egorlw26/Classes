#include "Plane.h"



Plane::Plane(const Vec3<float>& a, const Vec3<float>& b, const Vec3<float>& c, const Color & color)
	:A(a), B(b), C(c), m_color(color)
{
	AB = B - A;
	AC = C - A;
}

bool Plane::intersectWithRay(const Ray & ray, Vec3<float>& intersection)
{
	Vec4<float> equation;
	this->createEquation(equation);
	Vec3<float> normal(equation.x, equation.y, equation.z);

	Vec3<float> origin = ray.getOrigin();
	Vec3<float> direction = ray.getDirection();

	float Vd = Vec3<float>::dot(normal, direction);
	if (Vd == 0)
		return false; //direction and plane are parallel

	float Vo = -(Vec3<float>::dot(normal, origin) + equation.w);

	float t = Vo / Vd;
	if (t < 0) //intersection behind origin
		return false;

	direction.normalize();
	intersection.x = origin.x + t * direction.x;
	intersection.y = origin.y + t * direction.y;
	intersection.z = origin.z + t * direction.z;

	return true;
}

bool Plane::createEquation(Vec4<float>& equation)
{
	if (AB.x / AC.x == AB.y / AC.y == AB.z / AC.z) //Are on one line?
		return false;

	equation.x = AB.y * AC.z - AC.y * AB.z;
	equation.y = -(AB.x*AC.z - AC.x*AB.z);
	equation.z = AB.x * AC.y - AC.x * AB.y;
	equation.w = -A.x * equation.x - A.y * equation.y - A.z * equation.z;
	if (equation.x < 0)
		equation.negative();

	return true;
}

void Plane::createLocus()
{

}

void Plane::createVolumeBox()
{

}