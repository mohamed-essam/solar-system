#include "ApplicationManager.h"
#include<iostream>
#include"EventHandler.h"
using namespace std;

 int ApplicationManager:: screenWidth=0;
 int ApplicationManager::screenHeight=0;
 Renderer* ApplicationManager::mRenderer = 0;
 float ApplicationManager::mouseX = 0, ApplicationManager::mouseY = 0;
 GLFWwindow* ApplicationManager::mWindow=0;
void ApplicationManager::initialize() {

	initializeWindow();
	mRenderer = new Renderer();
	mRenderer->Initialize();
	mRenderer->UpdateAspectRatio(screenRatio);
	mTime = glfwGetTime();
}

void ApplicationManager::updateScreen() {
	float time = (float)(glfwGetTime() - mTime);
	mTime = glfwGetTime();
	mRenderer->Update(time);
	//mRenderer->getCamera()->setRotation(0.0, 0.0, 0.0);
	mRenderer->Draw();
	glfwSwapBuffers(mWindow); 
	glfwPollEvents();
	keyPressed = -1;
	glfwSetCursorPos(mWindow, screenWidth / 2, screenHeight / 2);
}
 void ApplicationManager::initializeWindow()
 {
	 if (!glfwInit())
	 {
		 fprintf(stderr, "Failed to initialize GLFW\n");
		 return;
	 }

	 glfwWindowHint(GLFW_SAMPLES, 4);
	 glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	 glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	 glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	 glfwWindowHint(GLFW_RESIZABLE, false);

	 GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	 const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	 screenRatio = (float)mode->width / (mode->height);
	 screenWidth = mode->width;
	 screenHeight = mode->height;
	 mouseX = (float)screenWidth / 2;
	 mouseY = (float)screenHeight / 2;

	 mWindow = glfwCreateWindow(screenWidth, screenHeight, "3D Solar System", NULL, NULL);
	
	 if (mWindow == NULL) {
		 fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		 glfwTerminate();
		 return;
	 }
	 glfwMakeContextCurrent(mWindow);

	 glewExperimental = true;
	 if (glewInit() != GLEW_OK) {
		 fprintf(stderr, "Failed to initialize GLEW\n");
		 return;
	 }
	 glfwSetInputMode(mWindow, GLFW_STICKY_KEYS, GL_TRUE);
	 glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	 EventHandler::setHandlers(this);
		 
 }
 vec2 ApplicationManager::getMousePosition()
 {
	 return vec2(mouseX,mouseY);
 }
 vec2 ApplicationManager::getscreenResolution()
 {
	 return vec2(screenWidth,screenHeight);
 }
 void ApplicationManager::resetMousePosition()
 {
	 mouseX =(float) screenWidth / 2;
	 mouseY = (float)screenHeight / 2;
 }
 GLFWwindow * ApplicationManager::getWindow()
 {
	 return mWindow;
 }
 Renderer * ApplicationManager::getRenderer()
 {
	 return mRenderer;
 }

bool ApplicationManager::isWindowNotClosing()
{
	return glfwGetKey(mWindow, GLFW_KEY_ESCAPE) != GLFW_PRESS &&glfwWindowShouldClose(mWindow) == 0;
}

ApplicationManager::~ApplicationManager()
{
	terminate();
}

void ApplicationManager::terminate() {
	glfwTerminate();
	delete mRenderer;
}