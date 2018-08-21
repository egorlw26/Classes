#pragma once
#include "../Math/Math.h"

class Camera
{
public:
	Camera(const Vec3<float> &position, const Vec3<float> &viewCenter, const Vec3<float> &up = Vec3<float>(0, 1, 0));

	Matrix4x4<float> lookAt(Vec3<float> position, Vec3<float> viewCenter, Vec3<float> up);

	void setPosition(const Vec3<float>& newPosition);
	void setViewCenter(const Vec3<float>& newViewCenter);
	void setUpVector(const Vec3<float>& newUpVector);

	const Vec3<float>& getPosition() const;
	const Vec3<float>& getViewCenter() const;
	const Vec3<float>& getUpVector() const;
	const Matrix4x4<float>& getView() const;

private:
	Vec3<float> m_upVector;
	Vec3<float> m_viewCenter;
	Vec3<float> m_position;

	Matrix4x4<float> m_view;
};
