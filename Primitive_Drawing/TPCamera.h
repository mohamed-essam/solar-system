#pragma once
#include <glm/glm.hpp>
#include "Camera.h"
class TPCamera : public Camera
{
	vec3 mObjectPosition;
	float mDistance;
public:
	TPCamera();

	void Yaw(float angle);
	void Pitch(float angle);
	void Roll(float angle);

	void Walk(float distance);
	void Strafe(float distance);
	void Fly(float distance);

	void UpdateViewMatrix();
	void Update(double time);
	void setDistance(float distance);

	~TPCamera();
};
