#include "Renderer.h"


void Renderer::UpdateAspectRatio(float ar) {
	projectionMatrix = glm::perspective(45.0f, ar, 0.1f, 10000.0f);
}

void Renderer::Initialize()
{
	GLuint VertexArrayID;

	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	shapes = new Shape[11];
	shapeCount = 11;

	GLfloat* v;
	GLint* e;
	int vc, ec;
	Shape::generateSphere(1,90,90,v, e, vc, ec);
	shapes[0] = Shape(vc / 8, 8, ec);
	shapes[0].color = glm::vec3(1.0f, 1.0f, 0.0f);
	for (int i = 3; i < 6; i++)
	{
		for (int j = 0; j < vc / 8; j++)
		{
			v[j * 8 + i] *= -1;
		}
	}
	for (int i = 0; i < vc; i++)
	{
		shapes[0].verts[i] = v[i];
	}
	for (int i = 0; i < ec; i++)
	{
		shapes[0].indices[i] = e[i];
	}

	shapes[0].generateBuffers();
	shapes[0].gloss = 0.0f;
	shapes[10] = shapes[0];
	shapes[0].rotationSelfRate = glm::vec3(0.0f, 5.0f, 0.0f);
	shapes[10].scale = glm::vec3(1000.0f);
	shapes[10].gloss = 0.0f;

	for (int i = 3; i < 6; i++)
	{
		for (int j = 0; j < vc / 8; j++)
		{
			v[j * 8 + i] *= -1;
		}
	}
	for (int i = 0; i < vc; i++)
	{
		shapes[0].verts[i] = v[i];
	}

	shapes[1] = shapes[0];
	shapes[1].color = glm::vec3(0.4f, 0.4f, 0.0f);
	shapes[1].position.x = -4;
	shapes[1].rotationSelf = glm::vec3(45.0f, 0.0f, 0.0f);
	shapes[1].rotationRate = glm::vec3(0.0f, 10.0f, 0.0f);
	shapes[1].rotationSelfRate = glm::vec3(0.0f, 20.0f, 0.0f);
	shapes[1].scale = glm::vec3(0.1f);
	shapes[1].gloss = 1.0f;
	shapes[1].generateBuffers();
	shapes[1].isSkyBox = false;
	shapes[0].isSkyBox = false;

	shapes[2] = shapes[1];
	shapes[2].color = glm::vec3(0.9f, 0.4f, 0.0f);
	shapes[2].position.x = -7;
	shapes[2].rotationSelf = glm::vec3(45.0f, 0.0f, 0.0f);
	shapes[2].rotationRate = glm::vec3(0.0f, 5.0f, 0.0f);
	shapes[2].rotationSelfRate = glm::vec3(0.0f, 10.0f, 0.0f);
	shapes[2].scale = glm::vec3(0.2f);
	shapes[2].isSkyBox = false;

	shapes[3] = shapes[1];
	shapes[3].color = glm::vec3(0.0f, 0.3f, 1.0f);
	shapes[3].position.x = -10;
	shapes[3].rotationSelf = glm::vec3(45.0f, 0.0f, 0.0f);
	shapes[3].rotationRate = glm::vec3(0.0f, 7.0f, 0.0f);
	shapes[3].rotationSelfRate = glm::vec3(0.0f, 25.0f, 0.0f);
	shapes[3].scale = glm::vec3(0.3f);
	shapes[3].isSkyBox = false;

	shapes[4] = shapes[1];
	shapes[4].color = glm::vec3(0.8f, 0.0f, 0.0f);
	shapes[4].position.x = -14;
	shapes[4].rotationSelf = glm::vec3(45.0f, 0.0f, 0.0f);
	shapes[4].rotationRate = glm::vec3(0.0f, 3.0f, 0.0f);
	shapes[4].rotationSelfRate = glm::vec3(0.0f, 15.0f, 0.0f);
	shapes[4].scale = glm::vec3(0.3f);
	shapes[4].isSkyBox = false;

	shapes[5] = shapes[1];
	shapes[5].color = glm::vec3(0.8f, 0.0f, 0.0f);
	shapes[5].position.x = -19;
	shapes[5].rotationSelf = glm::vec3(45.0f, 0.0f, 0.0f);
	shapes[5].rotationRate = glm::vec3(0.0f, 13.0f, 0.0f);
	shapes[5].rotationSelfRate = glm::vec3(0.0f, 15.0f, 0.0f);
	shapes[5].scale = glm::vec3(0.6f);
	shapes[5].isSkyBox = false;

	shapes[6] = shapes[1];
	shapes[6].color = glm::vec3(0.8f, 0.0f, 0.0f);
	shapes[6].position.x = -23;
	shapes[6].rotationSelf = glm::vec3(45.0f, 0.0f, 0.0f);
	shapes[6].rotationRate = glm::vec3(0.0f, 7.5f, 0.0f);
	shapes[6].rotationSelfRate = glm::vec3(0.0f, 15.0f, 0.0f);
	shapes[6].scale = glm::vec3(0.3f);
	shapes[6].isSkyBox = false;

	shapes[7] = shapes[1];
	shapes[7].color = glm::vec3(0.8f, 0.0f, 0.0f);
	shapes[7].position.x = -26;
	shapes[7].rotationSelf = glm::vec3(45.0f, 0.0f, 0.0f);
	shapes[7].rotationRate = glm::vec3(0.0f, 4.0f, 0.0f);
	shapes[7].rotationSelfRate = glm::vec3(0.0f, 15.0f, 0.0f);
	shapes[7].scale = glm::vec3(0.3f);
	shapes[7].isSkyBox = false;

	shapes[8] = shapes[1];
	shapes[8].color = glm::vec3(0.8f, 0.0f, 0.0f);
	shapes[8].position.x = -29;
	shapes[8].rotationSelf = glm::vec3(45.0f, 0.0f, 0.0f);
	shapes[8].rotationRate = glm::vec3(0.0f, 11.0f, 0.0f);
	shapes[8].rotationSelfRate = glm::vec3(0.0f, 15.0f, 0.0f);
	shapes[8].scale = glm::vec3(0.3f);
	shapes[8].isSkyBox = false;

	shapes[9] = shapes[1];
	shapes[9].color = glm::vec3(0.8f, 0.0f, 0.0f);
	shapes[9].position.x = -32;
	shapes[9].rotationSelf = glm::vec3(45.0f, 0.0f, 0.0f);
	shapes[9].rotationRate = glm::vec3(0.0f, 1.5f, 0.0f);
	shapes[9].rotationSelfRate = glm::vec3(0.0f, 15.0f, 0.0f);
	shapes[9].scale = glm::vec3(0.3f);
	shapes[9].isSkyBox = false;
	shapes[10].isSkyBox = true;

	GLuint programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

	glUseProgram(programID);

	matrixID = glGetUniformLocation(programID, "MVP");
	colorID = glGetUniformLocation(programID, "COLOR");
	lightColorID = glGetUniformLocation(programID, "LIGHT_COLOR");
	lightPositionID = glGetUniformLocation(programID, "LIGHT_POSITION");
	ambientLightColorID = glGetUniformLocation(programID, "AMBIENT_LIGHT_COLOR");
	cameraPositionID = glGetUniformLocation(programID, "CAMERA_POSITION");
	modelMatID = glGetUniformLocation(programID, "ModelMat");
	glossID = glGetUniformLocation(programID, "GLOSS");
	Light light(ambientLightColorID, lightColorID, lightPositionID, glm::vec3(0.3f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	mCamera = new FPCamera();
	mCamera->Fly(50.0f);
	mCamera->UpdateViewMatrix();

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	shapes[1].tex = new Texture("mercury.jpg", 0);
	shapes[2].tex = new Texture("venus.jpg", 1);
	shapes[3].tex = new Texture("earth.jpg", 2);
	shapes[4].tex = new Texture("mars.jpg", 3);
	shapes[5].tex = new Texture("jupiter.jpg", 4);
	shapes[6].tex = new Texture("saturn.jpg", 5);
	shapes[7].tex = new Texture("uranus.jpg", 6);
	shapes[8].tex = new Texture("neptune.jpg", 7);
	shapes[9].tex = new Texture("pluto.jpg", 8);
	shapes[0].tex = new Texture("sun.jpg", 9);
	shapes[10].tex = new Texture("stars.png", 10);
}

void Renderer::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int i = 0; i < shapeCount; i++)
	{
		shapes[i].render(matrixID, colorID, projectionMatrix, mCamera->getViewMatrix(), modelMatID, glossID);
	}
}

void Renderer::handleMouseScroll(bool up)
{
	if (!up)//scroll down
	{
		mCamera->Walk(-1);
	}
	else//scroll up
	{
		mCamera->Walk(1);
	}
}

#define SMALL_NUM  0.00000001
#define dot(u,v)   ((u).x * (v).x + (u).y * (v).y + (u).z * (v).z)

// intersect_RayTriangle(): intersect a ray with a 3D triangle
//    Input:  a ray R, and a triangle T
//    Output: *I = intersection point (when it exists)
//    Return: -1 = triangle is degenerate (a segment or point)
//             0 = disjoint (no intersect)
//             1 = intersect in unique point I1
//             2 = are in the same plane


void Renderer::Update(double time) {
	for (int i = 0; i < shapeCount; i++)
	{
		shapes[i].update(time);
	}
	glm::vec3 oldPosition = mCamera->getPosition();
	mCamera->Update(time);
	glm::vec3 newPosition = mCamera->getPosition();
	for (int i = 0; i < shapeCount; i++)
	{
		double radius = shapes[i].scale.x;
		glm::vec4 center = shapes[i].modelMatrix * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
		if (!shapes[i].isSkyBox &&glm::length(glm::vec4(newPosition, center.w) - center) < radius + 0.5f)
		{
			glm::vec4 temporary = glm::vec4(newPosition, center.w) - center;
			temporary = glm::normalize(temporary);
			temporary *= (radius + 0.75f);
			temporary += center;
			newPosition.x = temporary.x;
			newPosition.y = temporary.y;
			newPosition.z = temporary.z;

		}
		else if (shapes[i].isSkyBox &&glm::length(glm::vec4(newPosition, center.w) - center) > radius - 0.5f)

		{
			glm::vec4 temporary = glm::vec4(newPosition, center.w) - center;
			temporary = glm::normalize(temporary);
			temporary *= (radius - 0.75f);
			temporary += center;
			newPosition.x = temporary.x;
			newPosition.y = temporary.y;
			newPosition.z = temporary.z;

		}

	}
	mCamera->setPosition(newPosition.x, newPosition.y, newPosition.z);
	mCamera->UpdateViewMatrix();
	glUniform3f(cameraPositionID, mCamera->getPosition().x, mCamera->getPosition().y, mCamera->getPosition().z);
}

FPCamera* Renderer::getCamera() {
	return mCamera;
}

void Renderer::handleKeyboardPress(int key, int action) {
	vec3 cameraVelocity = mCamera->getVelocity();
	if (action == GLFW_RELEASE) {
		switch (key) {
		case GLFW_KEY_W:
		case GLFW_KEY_S:
			mCamera->setVelocity(cameraVelocity.x, cameraVelocity.y, 0);
			break;
		case GLFW_KEY_A:
		case GLFW_KEY_D:
			mCamera->setVelocity(0, cameraVelocity.y, cameraVelocity.z);
			break;
		}
	}
	else {
		switch (key) {
		case GLFW_KEY_W:
			mCamera->setVelocity(cameraVelocity.x, cameraVelocity.y, 40);
			break;
		case GLFW_KEY_A:
			mCamera->setVelocity(40, cameraVelocity.y, cameraVelocity.z);
			break;
		case GLFW_KEY_S:
			mCamera->setVelocity(cameraVelocity.x, cameraVelocity.y, -40);
			break;
		case GLFW_KEY_D:
			mCamera->setVelocity(-40, cameraVelocity.y, cameraVelocity.z);
		}
	}
}

void Renderer::handleMouseMove(double movex, double movey) {
	mCamera->setRotation(movey / 2, movex / 2, mCamera->getRotation().roll);
}