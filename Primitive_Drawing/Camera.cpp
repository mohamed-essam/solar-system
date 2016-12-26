#include "Camera.h"
Camera::Camera()
{
}
mat4 Camera::getViewMatrix()
{
	return mViewMatrix;
}
vec3 Camera::getLookDirection()
{
	return -1.0f*mDirection;
}
vec3 Camera::getVelocity()
{
	return velocity;
}
vec3 Camera::getPosition()
{
	return mPosition;
}
Camera::CameraRotation Camera::getRotation()
{
	return mRotation;
}
void Camera::setRotation(float p, float y, float r)
{
	mRotation.pitch = p;
	mRotation.yaw = y;
	mRotation.roll = r;
}

void Camera::setPosition(float x, float y, float z)
{
	mPosition = vec3(x, y, z);
}

void Camera::setVelocity(float x, float y, float z)
{
	velocity = vec3(x, y, z);
}
Camera::~Camera()
{
}
