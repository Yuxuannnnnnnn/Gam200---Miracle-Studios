#pragma once
#include "framework.h"
#include "Resource.h"


#define MAX_LOADSTRING 100

void CreateConsole();


class WindowsSystem
{
private:
	// Global Variables:
	HINSTANCE hInst;                      // current instance
	WCHAR szTitle[MAX_LOADSTRING];        // The title bar text
	WCHAR szWindowClass[MAX_LOADSTRING];  // the main window class name
	HACCEL hAccelTable;
	HWND mainHWND;

	HDC m_windowDC;//global Window-device context
	HGLRC m_wglDC;//OpenGL-device context

	unsigned int windowWidth = 800; //1920
	unsigned int windowHeight = 600;  //91080

public:

	WindowsSystem(HINSTANCE hInstance, int nCmdShow);

	// Forward declarations of functions included in this code module:
	ATOM MyRegisterClass(HINSTANCE hInstance);
	BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
	bool Initialise();

	HWND Get_hwnd() const{return mainHWND;}
	//Getter function
	HACCEL get_hAccelTable() const;
	HDC get_m_windowDC() const;

};

