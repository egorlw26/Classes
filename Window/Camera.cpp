#include "Camera.h"

Camera::Camera(const Vec3<float>& position, const Vec3<float>& viewCenter, const Vec3<float>& up)
	:m_position(position)
	,m_viewCenter(viewCenter)
	,m_upVector(up)
{
	m_view = lookAt(position, viewCenter, up);
}

Matrix4x4<float> Camera::lookAt(Vec3<float> position, Vec3<float> viewCenter, Vec3<float> upVector)
{
	Vec3<float> forward = (position - viewCenter).normalize();
	Vec3<float> right = Vec3<float>::cross(upVector, forward);
	Vec3<float> up = Vec3<float>::cross(forward, right);
	float resMas[16] = {right.x,	right.y,	right.z,	0.0f,
						up.x,		up.y,		up.z,		0.0f,
						forward.x,	forward.y,	forward.z,	0.0f,
						-position.x,-position.y,-position.z,1.0f};
	return Matrix4x4<float>(resMas);
}

const Vec3<float>& Camera::getPosition() const
{
	return m_position;
}

const Vec3<float>& Camera::getViewCenter() const
{
	return m_viewCenter;
}

const Vec3<float>& Camera::getUpVector() const
{
	return m_upVector;
}

const Matrix4x4<float>& Camera::getView() const
{
	return m_view;
}