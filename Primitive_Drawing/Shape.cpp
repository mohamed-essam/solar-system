#include "Shape.h"


Shape& Shape::operator=(const Shape& sh) {// copy values
	vertexCount = sh.vertexCount;
	attributeCount = sh.attributeCount;
	for (int i = 0; i < vertexCount; i++)
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
	VO = sh.VO;
	VAO = sh.VAO;
	finalTranslation = sh.finalTranslation;
	indicesCount = sh.indicesCount;
	for (int i = 0; i < indicesCount; i++)
	{
		indices[i] = sh.indices[i];
	}
	gloss = sh.gloss;
	skyBox = sh.skyBox;
	return *this;
}
void Shape::shallowCopy(const Shape& sh)//shallow copy
{
	vertexCount = sh.vertexCount;
	attributeCount = sh.attributeCount;
	verts = sh.verts;
	modelMatrix = sh.modelMatrix;
	position = sh.position;
	velocity = sh.velocity;
	rotation = sh.rotation;
	rotationRate = sh.rotationRate;
	rotationSelf = sh.rotationSelf;
	rotationSelfRate = sh.rotationSelfRate;
	scale = sh.scale;
	VO = sh.VO;
	VAO = sh.VAO;
	finalTranslation = sh.finalTranslation;
	indicesCount = sh.indicesCount;
	indices = sh.indices;
	gloss = sh.gloss;
	skyBox = sh.skyBox;
}
Shape::Shape() {}
Shape::Shape(int vertexCount, int verticesCoordinatesCount, int indicesCount) {
	this->vertexCount = vertexCount;
	this->attributeCount = verticesCoordinatesCount;
	verts = new Vertex[vertexCount];
	modelMatrix = glm::mat4(1.0f);
	position = glm::vec3(0.0f);
	velocity = glm::vec3(0.0f);
	rotation = glm::vec3(0.0f);
	rotationRate = glm::vec3(0.0f);
	rotationSelf = glm::vec3(0.0f);
	rotationSelfRate = glm::vec3(0.0f);
	finalTranslation = glm::vec3(0.0f);
	scale = glm::vec3(1.0f);
	this->indicesCount = indicesCount;
	indices = new GLuint[indicesCount];
	gloss = 1.0f;
	skyBox = false;
}
void Shape::generateBuffers() {
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VO);
	glBindBuffer(GL_ARRAY_BUFFER, VO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)* attributeCount * vertexCount, verts, GL_STATIC_DRAW);
	glGenBuffers(1, &indicesBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)* indicesCount, indices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
}
void Shape::generateSphere(float radiusSize, unsigned int ringsNumber, unsigned int sectorsNumber, GLfloat*& vertices, GLuint*& indices)
{
	const unsigned int sectorsBoundry = (sectorsNumber - 1), ringsBoundry = (ringsNumber - 1);
	const unsigned verticesSize = ringsNumber * sectorsNumber * (3 + 3 + 2);
	const unsigned indicesSize = sectorsBoundry *ringsBoundry * 6;

	float const R = 1.0f / ringsBoundry;
	float const S = 1.0f / sectorsBoundry;

	unsigned int r, s;
	unsigned int verticesSizeCounter = 0;
	unsigned int indicesCounter = 0;
	float x, y, z;
	for (r = 0; r < ringsNumber; ++r) for (s = 0; s < sectorsNumber; ++s) {
		y = (float)sin(-3.1415f / 2 + 3.1415 * r * R);
		x = (float)cos(2 * 3.1415f * s * S) * (float)sin(3.1415 * r * R);
		z = (float)sin(2 * 3.1415f * s * S) * (float)sin(3.1415 * r * R);

		vertices[verticesSizeCounter++] = x * radiusSize;
		vertices[verticesSizeCounter++] = y * radiusSize;
		vertices[verticesSizeCounter++] = z * radiusSize;

		vertices[verticesSizeCounter++] = -x;
		vertices[verticesSizeCounter++] = -y;
		vertices[verticesSizeCounter++] = -z;

		vertices[verticesSizeCounter++] = s*S;
		vertices[verticesSizeCounter++] = r*R;

		if ((r != ringsBoundry) && (s != sectorsBoundry))
		{
			indices[indicesCounter++] = r * sectorsNumber + s; //1
			indices[indicesCounter++] = r * sectorsNumber + (s + 1); //2	
			indices[indicesCounter++] = (r + 1) * sectorsNumber + (s + 1); //3
			indices[indicesCounter++] = r * sectorsNumber + s; //1
			indices[indicesCounter++] = (r + 1) * sectorsNumber + (s + 1); //3
			indices[indicesCounter++] = (r + 1) * sectorsNumber + s; //4
		}
		else if (r != ringsBoundry) {
			indices[indicesCounter++] = r * sectorsNumber + s; //1
			indices[indicesCounter++] = r * sectorsNumber; //2	
			indices[indicesCounter++] = (r + 1) * sectorsNumber; //3
			indices[indicesCounter++] = r * sectorsNumber + s; //1
			indices[indicesCounter++] = (r + 1) * sectorsNumber; //3
			indices[indicesCounter++] = (r + 1) * sectorsNumber + s; //4
		}
	}
}

void Shape::generateShape(Shape *& shape, Shape **shapes, int objectNumber)
{
	const unsigned verticiesSize = 90 * 90 * (3 + 3 + 2);
	const unsigned indicesSize = 89 * 90 * 6;


	if (objectNumber == 0) {
		shape = new Shape(verticiesSize / 8, 8, indicesSize);//arrays are done only once for sun & sky box 
		GLfloat *tempVerts = reinterpret_cast<GLfloat*>(shape->verts);
		GLuint *tempIndices = reinterpret_cast<GLuint*>(shape->indices);
		Shape::generateSphere(1, 90, 90, tempVerts, tempIndices);
		shape->rotationSelfRate = glm::vec3(0.0f, 5.0f, 0.0f);
		shape->scale = glm::vec3(1.0f);
		shape->gloss = 0.0f;
		shape->skyBox = false;
		shape->generateBuffers();   //is done only once for sun & sky box 
		shape->ID = 0;
		shape->texture = new Texture("images/sun.jpg", 9);
	}
	else if (objectNumber == 1) {
		shape = new Shape(verticiesSize / 8, 8, indicesSize);//arrays are done only once for the rest of the shapes
		*shape = (*shapes[0]);

		for (int i = 0; i < verticiesSize / 8; i++)
		{
			for (int j = 0; j < 3; j++)
				shape->verts[i].normalsCord[j] *= -1;
		}
		shape->position.x = -4;
		shape->rotationSelf = glm::vec3(45.0f, 0.0f, 0.0f);
		shape->rotationRate = glm::vec3(0.0f, 10.0f, 0.0f);
		shape->rotationSelfRate = glm::vec3(0.0f, 20.0f, 0.0f);
		shape->scale = glm::vec3(0.1f);
		shape->gloss = 1.0f;
		shape->skyBox = false;
		shape->generateBuffers(); //is done only once for the rest of the shapes
		shape->ID = 1;
		shape->texture = new Texture("images/mercury.jpg", 0);
	}

	else if (objectNumber == 2) {
		shape = new Shape();  //shallow copy
		shape->shallowCopy(*shapes[1]);
		shape->position.x = -7;
		shape->rotationSelf = glm::vec3(45.0f, 0.0f, 0.0f);
		shape->rotationRate = glm::vec3(0.0f, 5.0f, 0.0f);
		shape->rotationSelfRate = glm::vec3(0.0f, 10.0f, 0.0f);
		shape->scale = glm::vec3(0.2f);
		shape->skyBox = false;
		shape->ID = 2;
		shape->texture = new Texture("images/venus.jpg", 1);
	}
	else if (objectNumber == 3) {
		shape = new Shape();  //shallow copy
		shape->shallowCopy(*shapes[1]);
		shape->position.x = -10;
		shape->rotationSelf = glm::vec3(45.0f, 0.0f, 0.0f);
		shape->rotationRate = glm::vec3(0.0f, 7.0f, 0.0f);
		shape->rotationSelfRate = glm::vec3(0.0f, 25.0f, 0.0f);
		shape->scale = glm::vec3(0.3f);
		shape->skyBox = false;
		shape->ID = 3;
		shape->texture = new Texture("images/earth.jpg", 2);
	}
	else if (objectNumber == 4) {
		shape = new Shape();  //shallow copy
		shape->shallowCopy(*shapes[1]);
		shape->position.x = -14;
		shape->rotationSelf = glm::vec3(45.0f, 0.0f, 0.0f);
		shape->rotationRate = glm::vec3(0.0f, 3.0f, 0.0f);
		shape->rotationSelfRate = glm::vec3(0.0f, 15.0f, 0.0f);
		shape->scale = glm::vec3(0.3f);
		shape->skyBox = false;
		shape->ID = 4;
		shape->texture = new Texture("images/mars.jpg", 3);
	}
	else if (objectNumber == 5) {
		shape = new Shape();  //shallow copy
		shape->shallowCopy(*shapes[1]);
		shape->position.x = -19;
		shape->rotationSelf = glm::vec3(45.0f, 0.0f, 0.0f);
		shape->rotationRate = glm::vec3(0.0f, 13.0f, 0.0f);
		shape->rotationSelfRate = glm::vec3(0.0f, 15.0f, 0.0f);
		shape->scale = glm::vec3(0.6f);
		shape->skyBox = false;
		shape->ID = 5;
		shape->texture = new Texture("images/jupiter.jpg", 4);
	}
	else if (objectNumber == 6) {
		shape = new Shape();  //shallow copy
		shape->shallowCopy(*shapes[1]);
		shape->position.x = -23;
		shape->rotationSelf = glm::vec3(45.0f, 0.0f, 0.0f);
		shape->rotationRate = glm::vec3(0.0f, 7.5f, 0.0f);
		shape->rotationSelfRate = glm::vec3(0.0f, 15.0f, 0.0f);
		shape->scale = glm::vec3(0.3f);
		shape->skyBox = false;
		shape->ID = 6;
		shape->texture = new Texture("images/saturn.jpg", 5);
	}
	else if (objectNumber == 7) {
		shape = new Shape();  //shallow copy
		shape->shallowCopy(*shapes[1]);
		shape->position.x = -26;
		shape->rotationSelf = glm::vec3(45.0f, 0.0f, 0.0f);
		shape->rotationRate = glm::vec3(0.0f, 4.0f, 0.0f);
		shape->rotationSelfRate = glm::vec3(0.0f, 15.0f, 0.0f);
		shape->scale = glm::vec3(0.3f);
		shape->skyBox = false;
		shape->ID = 7;
		shape->texture = new Texture("images/uranus.jpg", 6);
	}
	else if (objectNumber == 8) {
		shape = new Shape();  //shallow copy
		shape->shallowCopy(*shapes[1]);
		shape->position.x = -29;
		shape->rotationSelf = glm::vec3(45.0f, 0.0f, 0.0f);
		shape->rotationRate = glm::vec3(0.0f, 11.0f, 0.0f);
		shape->rotationSelfRate = glm::vec3(0.0f, 15.0f, 0.0f);
		shape->scale = glm::vec3(0.3f);
		shape->skyBox = false;
		shape->ID = 8;
		shape->texture = new Texture("images/neptune.jpg", 7);
	}
	else if (objectNumber == 9) {
		shape = new Shape();  //shallow copy
		shape->shallowCopy(*shapes[1]);
		shape->position.x = -32;
		shape->rotationSelf = glm::vec3(45.0f, 0.0f, 0.0f);
		shape->rotationRate = glm::vec3(0.0f, 1.5f, 0.0f);
		shape->rotationSelfRate = glm::vec3(0.0f, 15.0f, 0.0f);
		shape->scale = glm::vec3(0.3f);
		shape->skyBox = false;
		shape->ID = 9;
		shape->texture = new Texture("images/pluto.jpg", 8);
	}
	else if (objectNumber == 10) {
		shape = new Shape();  //shallow copy
		shape->shallowCopy(*shapes[0]);
		shape->rotationSelfRate = glm::vec3(0.0f);
		shape->scale = glm::vec3(300.0f);
		shape->gloss = 0.0f;
		shape->skyBox = true;
		shape->ID = 10;
		shape->texture = new Texture("images/stars.png", 10);
	}

}

bool Shape::isSkyBox()const
{
	return skyBox;
}

vec3 Shape::getScale()const
{
	return scale;
}

mat4 Shape::getModelMatrix()const
{
	return modelMatrix;
}

Shape::~Shape() {
	if (ID == 0 || ID == 1) {
		delete[] verts;
		delete[] indices;
		glDeleteBuffers(1, &VO);
		glDeleteVertexArrays(1, &VAO);
	}
	delete texture;
}


void Shape::update(float delta) {
	position += delta * velocity;
	rotation += rotationRate * delta;
	rotationSelf += rotationSelfRate * delta;
	glm::mat4 rotationSelfMatrix = glm::rotate(rotationSelf.x, 1.0f, 0.0f, 0.0f) * glm::rotate(rotationSelf.y, 0.0f, 1.0f, 0.0f) * glm::rotate(rotationSelf.z, 0.0f, 0.0f, 1.0f);
	glm::mat4 rotationMatrix = glm::rotate(rotation.x, 1.0f, 0.0f, 0.0f) * glm::rotate(rotation.y, 0.0f, 1.0f, 0.0f) * glm::rotate(rotation.z, 0.0f, 0.0f, 1.0f);
	//modelMatrix = glm::translate(finalTranslation) * rotationMatrix * glm::translate(position) * rotationSelfMatrix * glm::scale(scale);
	modelMatrix = rotationMatrix * glm::translate(position) * rotationSelfMatrix * glm::scale(scale);
}

void Shape::render(GLuint matrixID, GLuint colorID, glm::mat4& projectionMatrix, glm::mat4& viewMatrix, GLuint modelID, GLuint glossID) {
	glBindVertexArray(VAO);
	texture->Bind();
	glm::mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;
	glUniform1f(glossID, gloss);
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(modelID, 1, GL_FALSE, &modelMatrix[0][0]);
	glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, (void*)0);
}