#include "Renderer.h"


void Renderer::UpdateAspectRatio(float aspectRatio) {
	projectionMatrix = glm::perspective(45.0f, aspectRatio, 0.1f, 10000.0f);
}

void Renderer::Initialize()
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	shapesCount = 11;

	shapes = new Shape*[shapesCount];
	for (int i = 0; i < shapesCount; ++i)
	{
		Shape::generateShape(shapes[i], shapes, i);
	}

	programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");
	glUseProgram(programID);

	matrixID = glGetUniformLocation(programID, "MVP");
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

}

void Renderer::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int i = 0; i < shapesCount; i++)
	{
		shapes[i]->render(matrixID, colorID, projectionMatrix, mCamera->getViewMatrix(), modelMatID, glossID);
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

void Renderer::Update(float time) {
	for (int i = 0; i < shapesCount; i++)
	{
		shapes[i]->update(time);
	}
	vec3 oldPosition = mCamera->getPosition();// save for collision
	mCamera->Update(time);
	vec3 newPosition = mCamera->getPosition();
	CollisionDetector::colliderPosition(shapes, shapesCount, oldPosition, newPosition);
	mCamera->setPosition(newPosition.x, newPosition.y, newPosition.z);
	mCamera->UpdateViewMatrix();
	glUniform3f(cameraPositionID, mCamera->getPosition().x, mCamera->getPosition().y, mCamera->getPosition().z);
}

FPCamera* Renderer::getCamera() {
	return mCamera;
}

Renderer::~Renderer()
{
	for (int i = 0; i < shapesCount; i++)
	{
		delete shapes[i];
	}
	delete[]shapes;
	delete mCamera;
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

void Renderer::handleMouseMove(float movex, float movey) {
	mCamera->setRotation(movey * 50, movex * 50, mCamera->getRotation().roll);
}