#pragma once

#include "Resource.h"

#include <exception>
#include "glew.h"

#include "ScreenSize.h" //For serialisation of Screen Resolution of the window



#define MAX_LOADSTRING 100


class Window
{
private:
	HINSTANCE hInst;                      // current instance
	WCHAR szTitle[MAX_LOADSTRING];        // The title bar text
	WCHAR szWindowClass[MAX_LOADSTRING];  // the main window class name


	//HACCEL hAccelTable;
	HWND mainHWND;

	HDC m_windowDC;//global Window-device context
	HGLRC m_wglDC;//OpenGL-device context

	unsigned _windowWidth; //1920
	unsigned _windowHeight;//1080


public:

	Window(HINSTANCE hInstance, int nCmdShow);
	bool Init();


	// Forward declarations of functions included in this code module:
	ATOM MyRegisterClass(HINSTANCE hInstance);
	BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);

	void SetFullscreenWindowMode(); //Used for In-Game Options, when Player set Game to fullscreen
	void SetNonFullScreenWindowMode(); //Used for In-Game Options, when Player set Game to non-fullscreen


	HWND Get_hwnd() const;					//Getter functions
	HDC get_m_windowDC() const;				//
	//HACCEL get_hAccelTable() const;		//
	HGLRC Get_m_wglDC() const;				//
											//
	unsigned GetWindowWidth() const;		//
	unsigned GetWindowHeight() const;		//

};

