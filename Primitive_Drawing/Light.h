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
#include <vector>
class Light
{
public:
	glm::vec3 position, color, ambientColor;
	Light(GLuint ambientColorId, GLuint lightColorId, GLuint lightPositionID, glm::vec3 ambientColor, glm::vec3 lightColor, glm::vec3 lightPosition );
	void applyLight(GLuint ambientColorId, GLuint lightColorId, GLuint lightPositionID, glm::vec3 ambientColor, glm::vec3 lightColor, glm::vec3 lightPosition);
	~Light();
};

