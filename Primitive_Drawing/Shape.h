#pragma once
#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <string.h>
#include "texture.h"
#include <vector>
using namespace glm;
class Shape {
	struct Vertex
	{
		GLfloat positionCord[3];
		GLfloat normalsCord[3];
		GLfloat texturesCord[2];

	};
	Vertex* verts;
	//GLfloat* verts;
	GLuint* indices;
	
	int ID;
	int attributeCount;
	int vertexCount;
	int indicesCount;
	bool skyBox;
	mat4 modelMatrix;
	vec3 position;
	vec3 velocity;
	vec3 rotationSelf;
	vec3 rotationSelfRate;
	vec3 rotation;
	vec3 rotationRate;
	vec3 scale;
	vec3 finalTranslation;
	GLuint VO;
	GLuint VAO;
	GLuint indicesBufferObject;
	Texture* texture;
	GLfloat gloss;
	static void generateSphere(float radiusSize, unsigned int ringsNumber, unsigned int sectorsNumber, GLfloat*& vs, GLuint*& e);
	void generateBuffers();
public:
	static void generateShape(Shape*&, Shape**, int);
	bool isSkyBox()const;
	vec3 getScale()const;
	mat4 getModelMatrix()const;
	Shape(int, int, int);
	void render(GLuint, GLuint, glm::mat4&, glm::mat4&, GLuint, GLuint);
	void update(float);
	Shape();
	void shallowCopy(const Shape&);
	Shape& operator=(const Shape&);
	~Shape();
};