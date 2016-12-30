#pragma once
#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "shader.hpp"
#include <gl/glfw3.h>
#include "Shape.h"
#include "FPCamera.h"
#include "texture.h"
#include "Light.h"
#include"CollisionDetector.h"

class Renderer
{
	GLuint programID;
	GLuint matrixID;
	GLuint colorID;
	GLuint lightColorID;
	GLuint ambientLightColorID;
	GLuint lightPositionID;
	GLuint cameraPositionID;
	GLuint modelMatID;
	GLuint glossID;
	float lastTime;
	Camera* mCamera;
	TPCamera thirdPersonCamera;
	FPCamera firstPersonCamera;
	Shape** shapes;
	int shapesCount;
	mat4 projectionMatrix;
	vec3 lightPosition;
	vec3 lightColor;
	vec3 ambientColor;
	float simulationSpeed;
public:

	void Initialize();
	void Draw();
	void handleMouseScroll(bool up);
	void Update(float);
	void UpdateAspectRatio(float);
	void handleKeyboardPress(int, int);
	void handleMouseMove(float, float);
	Camera* getCamera();
	~Renderer();
};
