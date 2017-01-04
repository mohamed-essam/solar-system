#include <iostream>
#include <Windows.h>
#include <gl/glew.h>
#include <gl/glfw3.h>
#include <thread>
#include "ApplicationManager.h"

 ApplicationManager* applicationManger;
bool InitGraphics();
extern "C" {
	__declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}
void playMainSound()
{
	mciSendString("open mainSound.mp3 alias mainSound", 0, 0, 0);
	mciSendString("play mainSound repeat", 0, 0, 0);
}
int main( void )
{
	
	//PlaySound("sound2.wav", NULL, SND_ASYNC | SND_LOOP|SND_FILENAME);

	mciSendString("open crash.mp3 alias crash", 0, 0, 0);
	std::thread helperThread(playMainSound);

	InitGraphics();
	mciSendString("close mainSound", 0, 0, 0);
	mciSendString("close crash", 0, 0, 0);
	helperThread.detach();
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

