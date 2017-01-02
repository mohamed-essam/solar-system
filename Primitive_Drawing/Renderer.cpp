#include "Renderer.h"


void Renderer::UpdateAspectRatio(float aspectRatio) {
	projectionMatrix = glm::perspective(45.0f, aspectRatio, 0.1f, 1000.0f);
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
	mCamera = &thirdPersonCamera;
	/*mCamera->Walk(-40.0f);
	mCamera->Fly(5.0f);
	mCamera->Pitch(5.0f);	
	mCamera->UpdateViewMatrix();*/
	isCollisionEnabled = true;
	isResumed = true;
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);// by default 
	glFrontFace(GL_CW);// by default 

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	simulationSpeed = 1.0f;
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
	TPCamera* tpcamera = dynamic_cast<TPCamera*>(mCamera);
	if (tpcamera == NULL)
	{
		if (!up)
			mCamera->Walk(-1);
		else
			mCamera->Walk(1);
	}
	else
	{
		if (!up)//scroll down
			tpcamera->setDistance(tpcamera->getDistance() + 1);
		else
			tpcamera->setDistance(tpcamera->getDistance() - 1);
	}
}

void Renderer::Update(float time) {
	time *= simulationSpeed;
	if(isResumed)
	for (int i = 0; i < shapesCount; i++)
	{
		shapes[i]->update(time);
	}
	vec3 oldPosition = mCamera->getPosition();// save for collision
	mCamera->Update(time / simulationSpeed);
	vec3 newPosition = mCamera->getPosition();
	if(isCollisionEnabled)
	CollisionDetector::colliderPosition(shapes, shapesCount, oldPosition, newPosition);
	mCamera->setPosition(newPosition.x, newPosition.y, newPosition.z);
	TPCamera* tpcamera = dynamic_cast<TPCamera*>(mCamera);
	if (tpcamera != NULL) {
		tpcamera->setDistance(length(newPosition));
	}
	mCamera->UpdateViewMatrix();
	glUniform3f(cameraPositionID, mCamera->getPosition().x, mCamera->getPosition().y, mCamera->getPosition().z);
}

Camera* Renderer::getCamera() {
	return mCamera;
}

Renderer::~Renderer()
{
	for (int i = 0; i < shapesCount; i++)
	{
		delete shapes[i];
	}

	delete[]shapes;
}

void Renderer::handleKeyboardPress(int key, int action) {
	if (key == GLFW_KEY_SPACE&&action == GLFW_RELEASE)
		isResumed = !isResumed;
	else if (key == GLFW_KEY_P&&action == GLFW_RELEASE)
		isCollisionEnabled = !isCollisionEnabled;
	else if (key == GLFW_KEY_C&&action == GLFW_RELEASE)
	{
		if (mCamera == &thirdPersonCamera)
		{
			firstPersonCamera.copy(thirdPersonCamera);
			mCamera = &firstPersonCamera;
		}
		else
		{
			thirdPersonCamera.copy(firstPersonCamera);
			mCamera = &thirdPersonCamera;
		}

	}
	TPCamera* tpcamera = dynamic_cast<TPCamera*>(mCamera);
	if (tpcamera == NULL)
	{//first person camera
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
			if (key == GLFW_KEY_W)
				mCamera->setVelocity(cameraVelocity.x, cameraVelocity.y, 10);
			else if (key == GLFW_KEY_A)
				mCamera->setVelocity(10, cameraVelocity.y, cameraVelocity.z);
			else if (key == GLFW_KEY_S)
				mCamera->setVelocity(cameraVelocity.x, cameraVelocity.y, -10);
			else if (key == GLFW_KEY_D)
				mCamera->setVelocity(-10, cameraVelocity.y, cameraVelocity.z);
		}
	}
	else
	{//third person camera
		if (key == GLFW_KEY_W)
			mCamera->setRotation(100, 0, mCamera->getRotation().roll);
		else if (key == GLFW_KEY_A)
			mCamera->setRotation(0,  100, mCamera->getRotation().roll);
		else if (key == GLFW_KEY_S)
			mCamera->setRotation(-100, 0, mCamera->getRotation().roll);
		else if (key == GLFW_KEY_D)
			mCamera->setRotation(0, -100, mCamera->getRotation().roll);
	}
	if (key == GLFW_KEY_UP && action != GLFW_RELEASE) {
		simulationSpeed += 0.1f;
	}
	else if (key == GLFW_KEY_DOWN && action != GLFW_RELEASE) {
		simulationSpeed -= 0.1f;
		if (simulationSpeed < 0.1f) simulationSpeed = 0.1f;
	}
}

void Renderer::handleMouseMove(float movex, float movey) {
	mCamera->setRotation(movey *50, movex *50, mCamera->getRotation().roll);
}