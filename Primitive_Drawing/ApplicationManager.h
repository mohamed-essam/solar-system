#pragma once
#include "Renderer.h"
#include <gl/glfw3.h>

using namespace glm;
class ApplicationManager
{
	int keyPressed;
	static float mouseX, mouseY;
	float screenRatio;
	static float screenWidth;
	static float screenHeight;
	static Renderer* mRenderer;
	double mTime;
	static GLFWwindow* mWindow;
	int windowWidth;
	int windowHeight;
	void initializeWindow();
public:
	static vec2 getMousePosition();
	static vec2 getscreenResolution();
	static void updateMousePosition(vec2);
	static GLFWwindow* getWindow();
	static Renderer* getRenderer();
	void initialize();
	void updateScreen();
	void terminate();
	bool isWindowNotClosing();
	~ApplicationManager();

};

