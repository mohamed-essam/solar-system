#pragma once
#include <glm/glm.hpp>
#include "Camera.h"
class TPCamera : public Camera
{
	vec3 mObjectPosition;
	float mDistance;
public:
	TPCamera();
	float getDistance();
	void Yaw(float angle);
	void Pitch(float angle);
	void Roll(float angle);

	void Walk(float distance);
	void Strafe(float distance);
	void Fly(float distance);

	void UpdateViewMatrix();
	void Update(float time);
	void setDistance(float distance);
	vec3 getTargetPosition();
	void setTargetPosition(vec3);
	~TPCamera();
};
