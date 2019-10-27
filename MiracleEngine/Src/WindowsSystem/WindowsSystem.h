#pragma once
#include "Window.h"

class WindowsSystem
{
private:
	
	HACCEL hAccelTable;
	MSG msg;
	Window window;

public:

	WindowsSystem(HINSTANCE hInstance, int nCmdShow);

	bool Update();//Update the window Object - reads all messages received in this window objects

	Window& getWindow(); //Getter function
	MSG& Get_msg();	//Setter and getter function

};

