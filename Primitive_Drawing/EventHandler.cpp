#include "EventHandler.h"
 ApplicationManager* EventHandler::applicationManger=0;
void EventHandler::setHandlers( ApplicationManager* Manger)
{
	applicationManger =(Manger);
	glfwSetScrollCallback(applicationManger->getWindow(), &(handleMouseScrolling));
	glfwSetKeyCallback(applicationManger->getWindow(), &(handleKeyPress));
	glfwSetCursorPosCallback(applicationManger->getWindow(), &(handleMouseMove));
}
void  EventHandler::handleKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods) {
	
	applicationManger->getRenderer()->handleKeyboardPress(key, action);
}

void EventHandler::handleMouseMove(GLFWwindow* window, double posx, double posy) {
	vec2 mousePosition = applicationManger->getMousePosition();
	vec2 screenResolution = applicationManger->getscreenResolution();
	applicationManger->getRenderer()->handleMouseMove((float)(-posx + mousePosition.x), (float)(posy - mousePosition.y));
	applicationManger->resetMousePosition();
}

void EventHandler::handleMouseScrolling(GLFWwindow *window, double x, double y)
{
	applicationManger->getRenderer()->handleMouseScroll(y > 0);
}