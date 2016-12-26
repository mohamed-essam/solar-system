#include <iostream>
#include <Windows.h>
#include <gl/glew.h>
#include <gl/glfw3.h>
#include "ApplicationManager.h"

 ApplicationManager* applicationManger;
bool InitGraphics();

int main( void )
{
	InitGraphics();
	return 0;
}

/** 
Creates the main window and initializes OpenGL stuff.
*/
bool InitGraphics()
{
	applicationManger = new ApplicationManager();
	applicationManger->initialize();
	
	do{
		applicationManger->updateScreen();
	} while (applicationManger->isWindowNotClosing());
	delete applicationManger;
	return true;
}

