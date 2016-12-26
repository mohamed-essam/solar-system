#include "Shape.h"

Shape::Shape(){}
Shape& Shape::operator=(const Shape& sh) {
	vertexCount = sh.vertexCount;
	attributeCount = sh.attributeCount;
	verts = new GLfloat[vertexCount * attributeCount];
	for (int i = 0; i < attributeCount * vertexCount; i++)
	{
		verts[i] = sh.verts[i];
	}
	modelMatrix = sh.modelMatrix;
	position = sh.position;
	velocity = sh.velocity;
	rotation = sh.rotation;
	rotationRate = sh.rotationRate;
	rotationSelf = sh.rotationSelf;
	rotationSelfRate = sh.rotationSelfRate;
	scale = sh.scale;
	bufferObject = sh.bufferObject;
	finalTranslation = sh.finalTranslation;
	indexCount = sh.indexCount;
	indices = new GLuint[indexCount];
	for (int i = 0; i < indexCount; i++)
	{
		indices[i] = sh.indices[i];
	}
	gloss = sh.gloss;
	return *this;
}

Shape::Shape(int vc, int ac, int ic) {
	vertexCount = vc;
	attributeCount = ac;
	verts = new GLfloat[vertexCount * attributeCount];
	modelMatrix = glm::mat4(1.0f);
	position = glm::vec3(0.0f);
	velocity = glm::vec3(0.0f);
	rotation = glm::vec3(0.0f);
	rotationRate = glm::vec3(0.0f);
	rotationSelf = glm::vec3(0.0f);
	rotationSelfRate = glm::vec3(0.0f);
	bufferObject = 1010;
	finalTranslation = glm::vec3(0.0f);
	scale = glm::vec3(1.0f);
	indexCount = ic;
	indices = new GLuint[indexCount];
	gloss = 1.0f;
}

void Shape::generateBuffers() {
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &bufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, bufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)* attributeCount * vertexCount, verts, GL_STATIC_DRAW);
	glGenBuffers(1, &indicesBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)* indexCount, indices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
}

Shape::~Shape() {
	delete[] verts;
	delete[] indices;
	glDeleteBuffers(1, &bufferObject);
	glDeleteVertexArrays(1, &VAO);
}


void Shape::update(float delta) {
	position += delta * velocity;
	rotation += rotationRate * delta;
	rotationSelf += rotationSelfRate * delta;
	glm::mat4 rotationSelfMatrix = glm::rotate(rotationSelf.x, 1.0f, 0.0f, 0.0f) * glm::rotate(rotationSelf.y, 0.0f, 1.0f, 0.0f) * glm::rotate(rotationSelf.z, 0.0f, 0.0f, 1.0f);
	glm::mat4 rotationMatrix = glm::rotate(rotation.x, 1.0f, 0.0f, 0.0f) * glm::rotate(rotation.y, 0.0f, 1.0f, 0.0f) * glm::rotate(rotation.z, 0.0f, 0.0f, 1.0f);
	modelMatrix = glm::translate(finalTranslation) * rotationMatrix * glm::translate(position) * rotationSelfMatrix * glm::scale(scale);
}

void Shape::render(GLuint matrixID, GLuint colorID, glm::mat4& projectionMatrix, glm::mat4& viewMatrix, GLuint modelID, GLuint glossID) {
	glBindVertexArray(VAO);
	tex->Bind();
	glm::mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;
	glUniform1f(glossID, gloss);
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(modelID, 1, GL_FALSE, &modelMatrix[0][0]);
	glUniform3f(colorID, color.x, color.y, color.z);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, (void*)0);
}