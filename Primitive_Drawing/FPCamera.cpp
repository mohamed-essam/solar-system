#include "FPCamera.h"

FPCamera::FPCamera()
{
	mPosition = vec3(0);
	mDirection = vec3(0, 0, -1);
	mUp = vec3(0, 1, 0);
	mRight = vec3(1, 0, 0);
	UpdateViewMatrix();
}


void FPCamera::Move(glm::vec3 dis) {
	glm::vec3 newPos = dis + mPosition;
	mPosition = newPos;
	// TODO : Check for collisions
}
void FPCamera::Walk(float distance) {
	Move(-mDirection * distance);
}

void FPCamera::Strafe(float distance) {
	Move(mRight * distance);
}

void FPCamera::Fly(float distance) {
	Move(mUp * distance);
}

void FPCamera::Roll(float angle) {
	mat4 rotationMat = rotate(angle, mDirection);
	vec4 tmp = rotationMat * vec4(mUp, 1.0f);
	mUp = vec3(tmp.x, tmp.y, tmp.z);
	tmp = rotationMat * vec4(mRight, 1.0f);
	mRight = vec3(tmp.x, tmp.y, tmp.z);
}

void FPCamera::Pitch(float angle) {
	mat4 rotationMat = rotate(angle, mRight);
	vec4 tmp = rotationMat * vec4(mUp, 1.0f);
	mUp = vec3(tmp.x, tmp.y, tmp.z);
	tmp = rotationMat * vec4(mDirection, 1.0f);
	mDirection = vec3(tmp.x, tmp.y, tmp.z);
}

void FPCamera::Yaw(float angle) {
	mat4 rotationMat = rotate(angle, mUp);
	vec4 tmp = rotationMat * vec4(mDirection, 1.0f);
	mDirection = vec3(tmp.x, tmp.y, tmp.z);
	tmp = rotationMat * vec4(mRight, 1.0f);
	mRight = vec3(tmp.x, tmp.y, tmp.z);
}

void FPCamera::UpdateViewMatrix() {
	vec3 center = mPosition + this->getLookDirection();
	mViewMatrix = lookAt(mPosition, center, mUp);
}

void FPCamera::Update(double time) {
	Walk(velocity.z * time);
	Strafe(velocity.x * time);
	Yaw(mRotation.yaw);
	Pitch(mRotation.pitch);
	Roll(mRotation.roll);
}

FPCamera::~FPCamera()
{
}