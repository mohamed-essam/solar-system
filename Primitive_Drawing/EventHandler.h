#pragma once
#include"ApplicationManager.h"

class EventHandler
{
	static ApplicationManager* applicationManger;
	void static handleKeyPress(GLFWwindow*, int, int, int, int);
	void static handleMouseMove(GLFWwindow*, double, double);
	void static handleMouseScrolling(GLFWwindow*, double, double);
public:
	
	void  static setHandlers( ApplicationManager* applicationManger);

};

