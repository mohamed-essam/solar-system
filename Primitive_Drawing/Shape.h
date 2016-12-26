#pragma once
#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <string.h>
#include "texture.h"
#include <vector>
class Shape{
public:
	static void generateSphere(float radiusSize, unsigned int ringsNumber, unsigned int sectorsNumber, GLfloat*& vs, GLint*& e, int& vSize, int& eSize);
	GLfloat* verts;
	GLint* indices;
	int attributeCount;
	int vertexCount;
	int indexCount;
	bool isSkyBox;
	glm::mat4 modelMatrix;
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 rotationSelf;
	glm::vec3 rotationSelfRate;
	glm::vec3 rotation;
	glm::vec3 rotationRate;
	glm::vec3 scale;
	glm::vec3 finalTranslation;
	glm::vec3 color;
	GLuint bufferObject;
	GLuint VAO;
	GLuint indicesBufferObject;
	Texture* tex;
	GLfloat gloss;

	~Shape();
	Shape();
	Shape(int, int, int);
	void render(GLuint, GLuint, glm::mat4&, glm::mat4&, GLuint, GLuint);
	void update(float);
	void generateBuffers();
	Shape& operator=(const Shape&);
};