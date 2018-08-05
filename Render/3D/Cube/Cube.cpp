#include "Cube.h"

Cube::Cube(const Vec3<float> &center, float edge)
	:m_center(center), m_edgeLength(edge),m_color(Color::Yellow)
{
	float halfEdge = m_edgeLength / 2;
	m_minX = m_center.x - halfEdge;
	m_maxX = m_center.x + halfEdge;
	m_minY = m_center.y - halfEdge;
	m_maxY = m_center.y + halfEdge;
	m_minZ = m_center.z - halfEdge;
	m_maxZ = m_center.z + halfEdge;
}

bool Cube::intersectWithRay(const Ray &ray)
{
	Vec3<float> rayStart = ray.getStart();
	Vec3<float> rayDirection = ray.getDirection();

	float tmin = (m_minX - rayStart.x) / rayDirection.x;
	float tmax = (m_maxX - rayStart.x) / rayDirection.x;
	if (tmax < tmin) 
		std::swap(tmin, tmax);

	float tymin = (m_minY - rayStart.y) / rayDirection.y;
	float tymax = (m_maxY - rayStart.y) / rayDirection.y;
	if (tymax < tymin) 
		std::swap(tymin, tymax);

	if (tmin > tymax || tymin > tmax)
		return false;

	if (tymin < tmin)
		tmin = tymin;
	if (tymax > tmax)
		tmax = tymax;

	float tzmin = (m_minZ - rayStart.z) / rayDirection.z;
	float tzmax = (m_maxZ - rayStart.z) / rayDirection.z;
	if (tzmax < tzmin)
		std::swap(tzmin, tzmax);

	if (tmin > tzmax || tmax < tzmin)
		return false;

	return true;
}

void Cube::createLocus()
{

}

void Cube::createVolumeBox()
{

}
