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
	FPCamera* mCamera;
	Shape* shapes;
	int shapeCount;
	glm::mat4 projectionMatrix;
	glm::vec3 lightPosition;
	glm::vec3 lightColor;
	glm::vec3 ambientColor;
public:

	void Initialize();
	void Draw();
	void Cleanup();
	void handleMouseScroll(bool up);
	void Update(double);
	void UpdateAspectRatio(float);
	void handleKeyboardPress(int, int);
	void handleMouseMove(double, double);
	FPCamera* getCamera();
};
