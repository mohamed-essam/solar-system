#include "TPCamera.h"

TPCamera::TPCamera()
{
	mUp = vec3(0, 1, 0);
	mRight = vec3(1, 0, 0);
	mDirection = vec3(0, 0, -1);
	mDistance = 50;
	mObjectPosition = vec3(0);
	UpdateViewMatrix();
}

float TPCamera::getDistance()
{
	return mDistance;
}

void TPCamera::Fly(float distance) {
	mPosition += distance * mUp;
	mObjectPosition += distance * mUp;
}

void TPCamera::Strafe(float distance) {
	mPosition += distance * mRight;
	mObjectPosition += distance * mRight;
}

void TPCamera::Walk(float distance) {
	mPosition -= distance * mDirection;
	mObjectPosition -= distance * mDirection;
}

void TPCamera::UpdateViewMatrix() {
	mPosition = mObjectPosition + (mDistance * mDirection);
	mViewMatrix = lookAt(mPosition, mObjectPosition, mUp);
}

void TPCamera::Yaw(float angle) {
	mRotation.yaw += angle;
	mat4 rotationMat = rotate(mRotation.yaw, mUp);
	vec4 tmp = rotationMat * vec4(mDirection, 1.0f);
	mDirection = vec3(tmp.x, tmp.y, tmp.z);
	tmp = rotationMat * vec4(mRight, 1.0f);
	mRight = vec3(tmp.x, tmp.y, tmp.z);
}

void TPCamera::Pitch(float angle) {
	mRotation.pitch += angle;
	mRotation.pitch = std::max(-90.0f, std::min(90.0f, mRotation.pitch));
	mat4 rotationMat = rotate(mRotation.pitch, mRight);
	vec4 tmp = rotationMat * vec4(mUp, 1.0f);
	mUp = vec3(tmp.x, tmp.y, tmp.z);
	tmp = rotationMat * vec4(mDirection, 1.0f);
	mDirection = vec3(tmp.x, tmp.y, tmp.z);
}

void TPCamera::Roll(float angle) {
	mRotation.roll += angle;
	mat4 rotationMat = rotate(mRotation.roll, mDirection);
	vec4 tmp = rotationMat * vec4(mUp, 1.0f);
	mUp = vec3(tmp.x, tmp.y, tmp.z);
	tmp = rotationMat * vec4(mRight, 1.0f);
	mRight = vec3(tmp.x, tmp.y, tmp.z);
}

void TPCamera::setDistance(float distance) {
	mDistance = distance;
}

void TPCamera::Update(float time) {
	mUp = vec3(0, 1, 0);
	mRight = vec3(1, 0, 0);
	mDirection = vec3(0, 0, -1);
	Yaw(mRotation.yawChange*time);
	Pitch(mRotation.pitchChange*time);
	Roll(mRotation.rollChange*time);
	mObjectPosition += mRight * velocity.x;
	mObjectPosition += mUp * velocity.y;
	mObjectPosition -= mDirection * velocity.z;
}

TPCamera::~TPCamera()
{
}
